/**
 * @file max11270.c
 * @brief FreeRTOS driver implementation for the MAX11270 24-bit ADC.
 *
 * Design:
 *   - The RDYB (data ready, active low) pin is wired to a GPIO/EXTI line.
 *     Its ISR calls max11270_isr_notify_from_gpio(), which gives a binary
 *     semaphore from ISR context.
 *   - A dedicated FreeRTOS task (max11270_reader_task) blocks on that
 *     semaphore, reads the 24-bit DATA register over SPI once data is
 *     ready, converts it to volts, and pushes the result to an output
 *     queue that the rest of the application consumes.
 *   - All SPI/GPIO access happens only from that one task, so no extra
 *     locking around the SPI bus is required from this driver's side.
 *     If you share the SPI bus with other peripherals, protect
 *     max11270_hal_spi_xfer()/cs() with a mutex in your HAL layer.
 */

#include "max11270.h"
#include "board_corrections.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

/* ------------------------------------------------------------------------ */
/* Low level register access                                                */
/* ------------------------------------------------------------------------ */

#define Max_Count_Unipolar 16777216.0f
#define Max_Count_Bipolar  8388608.0f

/* AC_HALFWAVE_CORRECTION is now defined in board_corrections.h, shared
 * with adc_dbm.cpp's polynomial dBm/Vac path - see that header for why. */

void max11270_write_reg(uint8_t addr, const uint8_t *data, uint8_t len)
{
    max11270_hal_cs(true);
    (void)max11270_hal_spi_xfer(MAX11270_REG_WRITE_CMD(addr));
    for (uint8_t i = 0; i < len; i++) {
        /* Registers are clocked MSB byte first */
        (void)max11270_hal_spi_xfer(data[i]);
    }
    max11270_hal_cs(false);
}

void max11270_read_reg(uint8_t addr, uint8_t *data, uint8_t len)
{
    max11270_hal_cs(true);
    (void)max11270_hal_spi_xfer(MAX11270_REG_READ_CMD(addr));
    for (uint8_t i = 0; i < len; i++) {
        data[i] = max11270_hal_spi_xfer(0x00u); /* dummy byte while clocking data out */
    }
    max11270_hal_cs(false);
}

void max11270_send_conv_cmd(uint8_t cal, uint8_t impd, max11270_rate_t rate)
{
    max11270_hal_cs(true);
    (void)max11270_hal_spi_xfer(MAX11270_CONV_CMD(cal, impd, rate));
    max11270_hal_cs(false);
}

void max11270_soft_reset(void)
{
    /* CTRL1: PD1=1, PD0=1 -> full register reset, equivalent to RSTB pin.
     * Keep other bits at 0/default for this one-shot write. */
    uint8_t ctrl1 = MAX11270_CTRL1_PD1 | MAX11270_CTRL1_PD0;
    max11270_write_reg(MAX11270_REG_CTRL1, &ctrl1, 1);
    /* Device also self-clears PD[1:0] back to 00 after reset; give it a
     * moment before further register access. */
    max11270_hal_delay_ms(2);
}

/* ------------------------------------------------------------------------ */
/* Helpers                                                                   */
/* ------------------------------------------------------------------------ */

static int32_t sign_extend_24(uint32_t v24)
{
    if (v24 & 0x00800000u) {
        return (int32_t)(v24 | 0xFF000000u); /* two's complement sign extend */
    }
    return (int32_t)v24;
}

static float raw_to_volts(const max11270_dev_t *dev, int32_t raw24)
{
    /* Full-scale is +/-VREF (bipolar) or 0..VREF (unipolar), over 2^23 or 2^24
     * codes respectively per Table 10. Divide out PGA gain since the PGA is
     * ahead of the ADC. */
    float gain = (dev->pga_gain > 0) ? (float)dev->pga_gain : 1.0f;
    float volts;

    if (dev->unipolar) {
        /* code range 0 .. 2^24-1 maps to 0 .. VREF (offset binary) */
        volts = ((float)(uint32_t)raw24 / Max_Count_Unipolar) * dev->vref / gain;
    } else {
        /* two's complement, +/-2^23 maps to +/-VREF */
        volts = ((float)raw24 / Max_Count_Bipolar) * dev->vref / gain;
    }

    return volts * AC_HALFWAVE_CORRECTION;
}

/* ------------------------------------------------------------------------ */
/* Reader task                                                               */
/* ------------------------------------------------------------------------ */

volatile uint32_t g_max11270_reader_beats = 0;

static void max11270_reader_task(void *pvParameters)
{
    max11270_dev_t *dev = (max11270_dev_t *)pvParameters;
    uint8_t raw_bytes[3];

    for (;;) {
        g_max11270_reader_beats++; /* one tick per loop iteration, whether or
                                     * not this pass actually got a sample */

        /* Block until the RDYB ISR signals a fresh conversion result.
         * Timeout is a safety net so the task can notice dev->running
         * being cleared even with no further conversions arriving. */
        if (xSemaphoreTake(dev->drdy_sem, pdMS_TO_TICKS(500)) == pdTRUE) {

            if (!dev->running) {
                break;
            }

            /* Read the 24-bit DATA register (assumes CTRL3:DATA32=0, the
             * power-on default). Reading it also deasserts RDYB. */
            max11270_read_reg(MAX11270_REG_DATA, raw_bytes, 3);

            uint32_t raw24 = ((uint32_t)raw_bytes[0] << 16) |
                              ((uint32_t)raw_bytes[1] << 8)  |
                              ((uint32_t)raw_bytes[2]);

            max11270_sample_t sample;
            sample.raw24 = dev->unipolar ? (int32_t)raw24 : sign_extend_24(raw24);
            /* AC_HALFWAVE_CORRECTION is applied inside raw_to_volts() below,
             * on the final float value - see its definition near the top
             * of this file for why it lives there rather than as a raw24
             * bit-shift here. Note sample.raw24 itself stays the true,
             * uncorrected ADC code - only .volts reflects the correction. */
            sample.volts = raw_to_volts(dev, sample.raw24);

            /* Optional: also fetch STAT to catch overrange/read errors.
             * Comment out for max throughput if you don't need it every
             * sample - it costs an extra SPI transaction. */
            uint8_t stat_bytes[2];
            max11270_read_reg(MAX11270_REG_STAT, stat_bytes, 2);
            sample.status = ((uint16_t)stat_bytes[0] << 8) | stat_bytes[1];

            /* Non-blocking send: if the consumer is too slow, drop the
             * oldest sample rather than stalling the ADC reader task. */
            if (xQueueSend(dev->out_queue, &sample, 0) != pdTRUE) {
                max11270_sample_t discard;
                (void)xQueueReceive(dev->out_queue, &discard, 0);
                (void)xQueueSend(dev->out_queue, &sample, 0);
            }
        } else {
            if (!dev->running) {
                break;
            }
            /* Timed out waiting for RDYB: nothing to do, loop and re-check
             * dev->running. If conversions should be running continuously
             * and you hit this repeatedly, check wiring / CTRL1 settings. */
        }
    }

    vTaskDelete(NULL);
}

/* ------------------------------------------------------------------------ */
/* ISR entry point                                                          */
/* ------------------------------------------------------------------------ */

void max11270_isr_notify_from_gpio(max11270_dev_t *dev, BaseType_t *pxHigherPriorityTaskWoken)
{
    /* Defensive: if the RDYB interrupt is armed (or fires spuriously due to
     * a floating/glitching pin) before max11270_init() has created the
     * semaphore, or after max11270_deinit() has destroyed it, dev->drdy_sem
     * is NULL. Calling xSemaphoreGiveFromISR() on a NULL handle trips a
     * FreeRTOS assert and reboots the whole board - always check first. */
    if (dev->drdy_sem != NULL) {
        xSemaphoreGiveFromISR(dev->drdy_sem, pxHigherPriorityTaskWoken);
    }
}

/* ------------------------------------------------------------------------ */
/* Init / deinit                                                            */
/* ------------------------------------------------------------------------ */

bool max11270_init(max11270_dev_t *dev,
                    float vref_volts,
                    max11270_pga_gain_t pga_gain,
                    bool unipolar,
                    bool continuous_mode,
                    max11270_rate_t rate,
                    UBaseType_t out_queue_len,
                    UBaseType_t task_priority,
                    uint16_t task_stack_size)
{
    memset(dev, 0, sizeof(*dev));
    dev->vref = vref_volts;
    dev->unipolar = unipolar;

    switch (pga_gain) {
        case MAX11270_PGA_GAIN_1:   dev->pga_gain = 1;   break;
        case MAX11270_PGA_GAIN_2:   dev->pga_gain = 2;   break;
        case MAX11270_PGA_GAIN_4:   dev->pga_gain = 4;   break;
        case MAX11270_PGA_GAIN_8:   dev->pga_gain = 8;   break;
        case MAX11270_PGA_GAIN_16:  dev->pga_gain = 16;  break;
        case MAX11270_PGA_GAIN_32:  dev->pga_gain = 32;  break;
        case MAX11270_PGA_GAIN_64:  dev->pga_gain = 64;  break;
        case MAX11270_PGA_GAIN_128: dev->pga_gain = 128; break;
        default:                    dev->pga_gain = 1;   break;
    }

    dev->drdy_sem = xSemaphoreCreateBinary();
    if (dev->drdy_sem == NULL) {
        return false;
    }

    dev->out_queue = xQueueCreate(out_queue_len, sizeof(max11270_sample_t));
    if (dev->out_queue == NULL) {
        vSemaphoreDelete(dev->drdy_sem);
        return false;
    }

    /* --- Reset and configure the part --- */
    max11270_soft_reset();

    /* CTRL2: PGA enabled at every gain setting (including 1x) for a
     * consistent signal path — matches max11270_set_gain()'s behavior so
     * runtime gain changes don't introduce a settling-time surprise. */
    uint8_t ctrl2 = MAX11270_CTRL2_PGAEN | ((uint8_t)pga_gain & 0x07u);
    max11270_write_reg(MAX11270_REG_CTRL2, &ctrl2, 1);

    /* CTRL1: unipolar/bipolar, continuous vs single-cycle, data format.
     * FORMAT=1 selects offset binary. Per the datasheet this only affects
     * BIPOLAR mode - unipolar mode is *always* offset binary regardless of
     * this bit - but it's set explicitly here so behavior stays correct if
     * you switch to bipolar later. */
    uint8_t ctrl1 = MAX11270_CTRL1_FORMAT;
    if (unipolar) {
        ctrl1 |= MAX11270_CTRL1_UB;
    }
    if (!continuous_mode) {
        ctrl1 |= MAX11270_CTRL1_SCYCLE; /* 1 = single-cycle mode */
    }
    /* CONTSC only matters together with SCYCLE; leave at 0 (continuous) */
    /* EXTCK left at 0 -> internal oscillator (default, no bit set here). */
    /* CTRL2's BUFEN was left unset above -> input buffers OFF (default). */
    max11270_write_reg(MAX11270_REG_CTRL1, &ctrl1, 1);

    /* GPIO1/GPIO2 -> external mux channel select, GPIO3 -> attenuator
     * enable (active-low). Configures all three as outputs and sets the
     * default state (channel 0, attenuator off). */
    max11270_gpio_init_outputs(dev);

    dev->rate    = rate;
    dev->running = true;

    BaseType_t ok = xTaskCreate(max11270_reader_task,
                                 "max11270",
                                 task_stack_size,
                                 dev,
                                 task_priority,
                                 &dev->task_handle);
    if (ok != pdPASS) {
        dev->running = false;
        vQueueDelete(dev->out_queue);
        vSemaphoreDelete(dev->drdy_sem);
        return false;
    }

    /* Run self-calibration before starting normal sampling. This trims the
     * chip's actual zero-scale/full-scale points - skipping it leaves the
     * part on whatever power-on trim it has, which can show a full-scale
     * range well short of VREF and trip AOR far earlier than expected.
     * self_calibrate() resumes continuous conversion itself afterward. */
    max11270_self_calibrate(dev);

    return true;
}

void max11270_deinit(max11270_dev_t *dev)
{
    dev->running = false;
    /* Give the semaphore once so the task wakes up, sees running==false,
     * and deletes itself instead of waiting for the 500ms timeout. */
    xSemaphoreGive(dev->drdy_sem);
    vTaskDelay(pdMS_TO_TICKS(10));

    /* Put part into standby (PD[1:0] = 10) to save power. */
    uint8_t ctrl1 = MAX11270_CTRL1_PD1;
    max11270_write_reg(MAX11270_REG_CTRL1, &ctrl1, 1);

    vQueueDelete(dev->out_queue);
    vSemaphoreDelete(dev->drdy_sem);
}

/* ------------------------------------------------------------------------ */
/* GPIO1-3 based external hardware control                                  */
/* ------------------------------------------------------------------------ */

/* IMPORTANT: the MAX11270 uses a single shared 8-bit command channel for
 * both "start a conversion" and "access a register". Issuing a register
 * write while a continuous conversion is running replaces/aborts that
 * conversion sequence - RDYB simply stops toggling afterward, with no
 * error reported anywhere. Every runtime reconfiguration function below
 * therefore re-issues the conversion command immediately after writing,
 * to resume continuous sampling. This is what was silently missing
 * before and is why gain changes killed sampling after the first one. */
static void max11270_resume_conversion(max11270_dev_t *dev)
{
    if (dev->running) {
        max11270_send_conv_cmd(0 /*cal*/, 0 /*impd*/, dev->rate);
    }
}

void max11270_gpio_init_outputs(max11270_dev_t *dev)
{
    /* All three GPIOs as outputs. Reserved bit3 is kept at its datasheet
     * default of 1. DIO3=1 -> GPIO3 idle high -> attenuator OFF, since the
     * attenuator's enable input is active-low. DIO1=DIO2=0 -> channel 0. */
    dev->ctrl4_shadow = MAX11270_CTRL4_DIR1 | MAX11270_CTRL4_DIR2 | MAX11270_CTRL4_DIR3 |
                         MAX11270_CTRL4_RESERVED3 | MAX11270_CTRL4_DIO3;
    dev->channel = 0;
    dev->attenuator_on = false;
    max11270_write_reg(MAX11270_REG_CTRL4, &dev->ctrl4_shadow, 1);
    max11270_resume_conversion(dev);
}

void max11270_set_channel(max11270_dev_t *dev, uint8_t channel)
{
    channel &= 0x03u;
    dev->channel = channel;

    dev->ctrl4_shadow &= (uint8_t)~(MAX11270_CTRL4_DIO1 | MAX11270_CTRL4_DIO2);
    if (channel & 0x01u) dev->ctrl4_shadow |= MAX11270_CTRL4_DIO1;
    if (channel & 0x02u) dev->ctrl4_shadow |= MAX11270_CTRL4_DIO2;

    max11270_write_reg(MAX11270_REG_CTRL4, &dev->ctrl4_shadow, 1);
    max11270_resume_conversion(dev);
}

void max11270_set_attenuator(max11270_dev_t *dev, bool enabled)
{
    dev->attenuator_on = enabled;

    if (enabled) {
        dev->ctrl4_shadow &= (uint8_t)~MAX11270_CTRL4_DIO3; /* active-low: 0 = ON */
    } else {
        dev->ctrl4_shadow |= MAX11270_CTRL4_DIO3;           /* 1 = OFF */
    }

    max11270_write_reg(MAX11270_REG_CTRL4, &dev->ctrl4_shadow, 1);
    max11270_resume_conversion(dev);
}

void max11270_set_gain(max11270_dev_t *dev, max11270_pga_gain_t gain)
{
    /* PGA is kept enabled for every gain setting (including 1x) so the
     * signal path and settling behavior stay consistent regardless of
     * gain. Buffers (BUFEN) and digital gain (DGAIN) stay off/x1 here,
     * matching max11270_init()'s defaults. */
    uint8_t ctrl2 = MAX11270_CTRL2_PGAEN | ((uint8_t)gain & 0x07u);
    max11270_write_reg(MAX11270_REG_CTRL2, &ctrl2, 1);

    switch (gain) {
        case MAX11270_PGA_GAIN_1:   dev->pga_gain = 1;   break;
        case MAX11270_PGA_GAIN_2:   dev->pga_gain = 2;   break;
        case MAX11270_PGA_GAIN_4:   dev->pga_gain = 4;   break;
        case MAX11270_PGA_GAIN_8:   dev->pga_gain = 8;   break;
        case MAX11270_PGA_GAIN_16:  dev->pga_gain = 16;  break;
        case MAX11270_PGA_GAIN_32:  dev->pga_gain = 32;  break;
        case MAX11270_PGA_GAIN_64:  dev->pga_gain = 64;  break;
        case MAX11270_PGA_GAIN_128: dev->pga_gain = 128; break;
        default:                    dev->pga_gain = 1;   break;
    }

    max11270_resume_conversion(dev);
}

void max11270_self_calibrate(max11270_dev_t *dev)
{
    /* CTRL5: which mode CAL=1 in the command byte selects is CTRL5:CAL[1:0]
     * (00 = self-calibration, the default). Here we make sure the self-cal
     * RESULTS actually get applied (NOSCO=NOSCG=0, matching power-on
     * default) and system-cal correction stays off since no system
     * calibration has been run (NOSYSO=NOSYSG=1, matching default).
     * Written explicitly in case CTRL5 was ever touched elsewhere. */
    uint8_t ctrl5 = MAX11270_CTRL5_NOSYSO | MAX11270_CTRL5_NOSYSG;
    max11270_write_reg(MAX11270_REG_CTRL5, &ctrl5, 1);

    /* Issuing any command interrupts a running conversion the same way any
     * other register/command write does; the CAL=1 command below starts a
     * fresh self-calibration sequence regardless of prior state. RATE bits
     * are ignored during calibration (datasheet: fixed internal 50sps). */
    max11270_send_conv_cmd(1 /*cal*/, 0 /*impd*/, dev->rate);

    /* Self-calibration runs two internal conversions (offset, then full
     * scale) and takes ~200ms total. Poll MSTAT in STAT rather than a
     * fixed delay, with a generous timeout in case something's wrong. */
    uint8_t stat_bytes[2];
    for (int i = 0; i < 50; i++) {  /* up to 50 x 10ms = 500ms */
        vTaskDelay(pdMS_TO_TICKS(10));
        max11270_read_reg(MAX11270_REG_STAT, stat_bytes, 2);
        uint16_t stat = ((uint16_t)stat_bytes[0] << 8) | stat_bytes[1];
        if (!(stat & MAX11270_STAT_MSTAT)) {
            break; /* MSTAT clear -> calibration finished */
        }
    }

    max11270_resume_conversion(dev);
}