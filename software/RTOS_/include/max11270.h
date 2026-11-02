/**
 * @file max11270.h
 * @brief Driver for the Maxim MAX11270 24-bit delta-sigma ADC, for use under FreeRTOS.
 *
 * Command byte and register map taken from the MAX11270 datasheet (19-7048; Rev 1; 5/15).
 *
 * SPI protocol summary (see datasheet "Modes and Registers"):
 *   Every transaction starts with an 8-bit command byte, MSB first.
 *
 *   Conversion command (MODE = 0):
 *     bit7=START(1) bit6=MODE(0) bit5=CAL bit4=IMPD bit3..0=RATE[3:0]
 *
 *   Register access command (MODE = 1):
 *     bit7=START(1) bit6=MODE(1) bit5..1=RS[4:0] (register addr) bit0=R/W (0=write,1=read)
 *
 * This file only defines the protocol + a hardware-independent API.
 * Port max11270_hal.c to your SPI/GPIO/FreeRTOS BSP.
 */

#ifndef MAX11270_H
#define MAX11270_H

#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* Command byte construction                                                */
/* ------------------------------------------------------------------------ */

#define MAX11270_START_BIT          0x80u
#define MAX11270_MODE_REGISTER      0x40u   /* MODE=1 -> register access   */
#define MAX11270_MODE_CONVERSION    0x00u   /* MODE=0 -> start conversion  */

/* Register access command byte: START | MODE=1 | addr<<1 | rw */
#define MAX11270_REG_WRITE_CMD(addr)  (MAX11270_START_BIT | MAX11270_MODE_REGISTER | (((addr) & 0x1Fu) << 1) | 0u)
#define MAX11270_REG_READ_CMD(addr)   (MAX11270_START_BIT | MAX11270_MODE_REGISTER | (((addr) & 0x1Fu) << 1) | 1u)

/* Conversion command byte: START | MODE=0 | CAL | IMPD | RATE[3:0] */
#define MAX11270_CONV_CMD(cal, impd, rate) \
    (MAX11270_START_BIT | MAX11270_MODE_CONVERSION | \
     (((cal)  & 0x1u) << 5) | \
     (((impd) & 0x1u) << 4) | \
     ((rate) & 0x0Fu))

/* ------------------------------------------------------------------------ */
/* Register address map (Table 8)                                          */
/* ------------------------------------------------------------------------ */

#define MAX11270_REG_STAT       0x00u  /* R,  16-bit  */
#define MAX11270_REG_CTRL1      0x01u  /* RW, 8-bit   */
#define MAX11270_REG_CTRL2      0x02u  /* RW, 8-bit   */
#define MAX11270_REG_CTRL3      0x03u  /* RW, 8-bit   */
#define MAX11270_REG_CTRL4      0x04u  /* RW, 8-bit   */
#define MAX11270_REG_CTRL5      0x05u  /* RW, 8-bit   */
#define MAX11270_REG_DATA       0x06u  /* R,  24/32-bit */
#define MAX11270_REG_SOC_SPI    0x07u  /* RW, 24-bit  */
#define MAX11270_REG_SGC_SPI    0x08u  /* RW, 24-bit  */
#define MAX11270_REG_SCOC_SPI   0x09u  /* RW, 24-bit  */
#define MAX11270_REG_SCGC_SPI   0x0Au  /* RW, 24-bit  */
#define MAX11270_REG_RAM        0x0Cu  /* special, see datasheet */
#define MAX11270_REG_SYNC_SPI   0x0Du  /* W, special  */
#define MAX11270_REG_SOC_ADC    0x15u  /* R,  24-bit  */
#define MAX11270_REG_SGC_ADC    0x16u  /* R,  24-bit  */
#define MAX11270_REG_SCOC_ADC   0x17u  /* R,  24-bit  */
#define MAX11270_REG_SCGC_ADC   0x18u  /* R,  24-bit  */

/* CTRL1 bits */
#define MAX11270_CTRL1_CONTSC   (1u << 0)  /* 1 = continuous conversions            */
#define MAX11270_CTRL1_SCYCLE   (1u << 1)  /* 1 = single-cycle mode                 */
#define MAX11270_CTRL1_FORMAT   (1u << 2)  /* bipolar format: 0=2's compl, 1=offset */
#define MAX11270_CTRL1_UB       (1u << 3)  /* 1 = unipolar, 0 = bipolar input range */
#define MAX11270_CTRL1_PD0      (1u << 4)
#define MAX11270_CTRL1_PD1      (1u << 5)
#define MAX11270_CTRL1_SYNCMODE (1u << 6)
#define MAX11270_CTRL1_EXTCK    (1u << 7)  /* 1 = external clock on CLK pin         */

/* CTRL2 bits (PGA gain, buffer) */
#define MAX11270_CTRL2_PGAG0    (1u << 0)
#define MAX11270_CTRL2_PGAG1    (1u << 1)
#define MAX11270_CTRL2_PGAG2    (1u << 2)
#define MAX11270_CTRL2_PGAEN    (1u << 3)
#define MAX11270_CTRL2_LPMODE   (1u << 4)
#define MAX11270_CTRL2_BUFEN    (1u << 5)
#define MAX11270_CTRL2_DGAIN0   (1u << 6)
#define MAX11270_CTRL2_DGAIN1   (1u << 7)

/* STAT register bits (16-bit) */
#define MAX11270_STAT_RDY       (1u << 0)
#define MAX11270_STAT_MSTAT     (1u << 1)
#define MAX11270_STAT_DOR       (1u << 2)  /* data overrange */
#define MAX11270_STAT_AOR       (1u << 8)  /* analog overrange */
#define MAX11270_STAT_RDERR     (1u << 9)

/* CTRL4 bits (GPIO1-3 direction and output value) */
#define MAX11270_CTRL4_DIO1        (1u << 0)  /* GPIO1 output value (or input readback) */
#define MAX11270_CTRL4_DIO2        (1u << 1)  /* GPIO2 output value (or input readback) */
#define MAX11270_CTRL4_DIO3        (1u << 2)  /* GPIO3 output value (or input readback) */
#define MAX11270_CTRL4_RESERVED3   (1u << 3)  /* datasheet default = 1; preserve as 1 */
#define MAX11270_CTRL4_DIR1        (1u << 4)  /* 0 = GPIO1 input, 1 = GPIO1 output */
#define MAX11270_CTRL4_DIR2        (1u << 5)  /* 0 = GPIO2 input, 1 = GPIO2 output */
#define MAX11270_CTRL4_DIR3        (1u << 6)  /* 0 = GPIO3 input, 1 = GPIO3 output */

/* CTRL5 bits (calibration control) */
#define MAX11270_CTRL5_NOSCO    (1u << 0)  /* 1 = disable use of self-cal offset  */
#define MAX11270_CTRL5_NOSCG    (1u << 1)  /* 1 = disable use of self-cal gain    */
#define MAX11270_CTRL5_NOSYSO   (1u << 2)  /* 1 = disable use of system offset    */
#define MAX11270_CTRL5_NOSYSG   (1u << 3)  /* 1 = disable use of system gain      */
#define MAX11270_CTRL5_CAL0     (1u << 6)  /* CAL[1:0]: 00=self-cal, 01=sys offset,*/
#define MAX11270_CTRL5_CAL1     (1u << 7)  /* 10=sys full-scale, 11=reserved       */

/* PGA gain settings for CTRL2 PGAG[2:0] (with PGAEN=1) */
typedef enum {
    MAX11270_PGA_GAIN_1   = 0x0,
    MAX11270_PGA_GAIN_2   = 0x1,
    MAX11270_PGA_GAIN_4   = 0x2,
    MAX11270_PGA_GAIN_8   = 0x3,
    MAX11270_PGA_GAIN_16  = 0x4,
    MAX11270_PGA_GAIN_32  = 0x5,
    MAX11270_PGA_GAIN_64  = 0x6,
    MAX11270_PGA_GAIN_128 = 0x7,
} max11270_pga_gain_t;

/* Conversion data rates, RATE[3:0], continuous mode / SCYCLE=0 (Table 9) */
typedef enum {
    MAX11270_RATE_1_9SPS   = 0x0,
    MAX11270_RATE_3_9SPS   = 0x1,
    MAX11270_RATE_7_8SPS   = 0x2,
    MAX11270_RATE_15_6SPS  = 0x3,
    MAX11270_RATE_31_2SPS  = 0x4,
    MAX11270_RATE_62_5SPS  = 0x5,
    MAX11270_RATE_125SPS   = 0x6,
    MAX11270_RATE_250SPS   = 0x7,
    MAX11270_RATE_500SPS   = 0x8,
    MAX11270_RATE_1000SPS  = 0x9,
    MAX11270_RATE_2000SPS  = 0xA,
    MAX11270_RATE_4000SPS  = 0xB,
    MAX11270_RATE_8000SPS  = 0xC,
    MAX11270_RATE_16000SPS = 0xD,
    MAX11270_RATE_32000SPS = 0xE,
    MAX11270_RATE_64000SPS = 0xF,
} max11270_rate_t;

/* ------------------------------------------------------------------------ */
/* Hardware abstraction layer - implement these for your MCU/BSP.           */
/* All calls happen from a normal task context (not from ISR), except the   */
/* DRDY ISR callback which the BSP is expected to invoke.                   */
/* ------------------------------------------------------------------------ */

/** Assert/deassert CSB (active low). */
void max11270_hal_cs(bool assert_low);

/** Full-duplex SPI byte transfer. Returns the byte shifted in on MISO/DOUT
 *  while tx_byte is shifted out on MOSI/DIN. SCLK must idle low, data
 *  sampled/shifted per the datasheet (mode compatible with SPI Mode 0). */
uint8_t max11270_hal_spi_xfer(uint8_t tx_byte);

/** Millisecond delay (used only during calibration waits). */
void max11270_hal_delay_ms(uint32_t ms);

/** Optional: level of RDYB pin, true = asserted (low). Not required if you
 *  rely purely on the EXTI/GPIO interrupt + semaphore. */
bool max11270_hal_rdyb_is_low(void);

/* ------------------------------------------------------------------------ */
/* Driver context                                                           */
/* ------------------------------------------------------------------------ */

typedef struct {
    int32_t  raw24;      /* sign-extended 24-bit conversion result           */
    float    volts;      /* converted using vref/gain, if configured         */
    uint16_t status;     /* STAT register snapshot read alongside, if used   */
} max11270_sample_t;

typedef struct {
    SemaphoreHandle_t drdy_sem;   /* given by GPIO ISR on RDYB falling edge  */
    QueueHandle_t     out_queue;  /* max11270_sample_t results delivered here */
    TaskHandle_t      task_handle;
    float             vref;       /* volts, for raw->volts conversion         */
    uint8_t           pga_gain;   /* 1,2,4,...128, matches configured PGA     */
    bool              unipolar;   /* true = 0..VREF, false = -VREF..VREF      */
    bool              running;
    uint8_t           ctrl4_shadow;  /* local mirror of CTRL4 (GPIO dir/data) */
    uint8_t           channel;       /* current external mux channel, 0-3     */
    bool              attenuator_on; /* current attenuator enable state       */
    max11270_rate_t   rate;          /* current conversion rate, so runtime   */
                                      /* register writes can resume sampling  */
} max11270_dev_t;

/** Incremented once per max11270_reader_task loop iteration (regardless of
 *  whether that iteration actually produced a sample or just timed out
 *  waiting on RDYB). A lightweight external liveness check that needs no
 *  FreeRTOS introspection API - if this stops advancing, the reader task
 *  has stopped doing work, whether it exited, crashed, or is stuck,
 *  independent of whether FreeRTOS still considers the task to "exist". */
extern volatile uint32_t g_max11270_reader_beats;

/** Low level: write `len` bytes (MSB first) to register `addr`. len is 1 for
 *  8-bit regs (CTRL1..CTRL5), 2 for STAT, 3 for 24-bit regs, 4 if DATA32=1. */
void max11270_write_reg(uint8_t addr, const uint8_t *data, uint8_t len);

/** Low level: read `len` bytes (MSB first) from register `addr`. */
void max11270_read_reg(uint8_t addr, uint8_t *data, uint8_t len);

/** Issue a conversion-mode command byte directly (start/stop/cal/power-down).
 *  cal: 1 = perform calibration (see CTRL5:CAL bits for which one)
 *  impd: 1 = power down after this command completes
 *  rate: one of max11270_rate_t                                            */
void max11270_send_conv_cmd(uint8_t cal, uint8_t impd, max11270_rate_t rate);

/** Reset the part via CTRL1 PD[1:0]=11 (software reset, equivalent to RSTB). */
void max11270_soft_reset(void);

/** One-time init: resets the part, configures CTRL1/CTRL2, creates the
 *  FreeRTOS semaphore + queue + task. Call max11270_isr_notify_from_gpio()
 *  from your EXTI/GPIO ISR for the RDYB pin (falling edge).
 *
 *  out_queue_len: depth of the sample queue.
 *  task_priority: FreeRTOS priority for the internal reader task.
 *  task_stack_size: stack size for the internal reader task, in the units
 *      your port's xTaskCreate() expects. IMPORTANT: on ESP-IDF /
 *      Arduino-ESP32 this is BYTES (not words as in vanilla FreeRTOS) -
 *      use at least 2048-4096 here, since the reader task walks through
 *      several calls (register read -> SPI transfer -> HAL) plus float
 *      conversion. Too small a value overflows silently until the stack
 *      canary trips and the board panics/reboots.
 *  Returns true on success. */
bool max11270_init(max11270_dev_t *dev,
                    float vref_volts,
                    max11270_pga_gain_t pga_gain,
                    bool unipolar,
                    bool continuous_mode,
                    max11270_rate_t rate,
                    UBaseType_t out_queue_len,
                    UBaseType_t task_priority,
                    uint16_t task_stack_size);

/** Call this from the RDYB GPIO interrupt (falling edge = data ready).
 *  Safe to call from ISR context. */
void max11270_isr_notify_from_gpio(max11270_dev_t *dev, BaseType_t *pxHigherPriorityTaskWoken);

/** Stop the reader task and put the part into standby. */
void max11270_deinit(max11270_dev_t *dev);

/* ------------------------------------------------------------------------ */
/* GPIO1-3 based external hardware control                                  */
/*   GPIO1 (LSB) + GPIO2 (MSB) drive a 2-bit code to an external 4:1 mux.   */
/*   GPIO3 drives an external attenuator's active-low enable input.        */
/*                                                                          */
/*   All of max11270_set_channel/set_attenuator/set_gain below write a     */
/*   control register while (typically) a continuous conversion is         */
/*   running. The MAX11270 shares one 8-bit command channel between        */
/*   "start conversion" and "access register" - a register write during   */
/*   continuous conversion silently aborts the running sequence, so each   */
/*   of these functions automatically re-issues the conversion command     */
/*   afterward (at the rate max11270_init() was called with) to resume     */
/*   sampling. Don't call max11270_write_reg() directly on other control   */
/*   registers while running without doing the same, or sampling will      */
/*   stop with no error indication - RDYB just stops toggling.             */
/* ------------------------------------------------------------------------ */

/** Configure GPIO1-3 as outputs (DIR1-3=1), channel=0, attenuator off.
 *  Called automatically by max11270_init(); exposed in case you need to
 *  reconfigure GPIO direction later (e.g. after max11270_soft_reset()). */
void max11270_gpio_init_outputs(max11270_dev_t *dev);

/** Drive GPIO1/GPIO2 with a 2-bit code (channel & 0x03) to steer an
 *  external 4:1 analog mux feeding AINP/AINN. GPIO1 = bit0, GPIO2 = bit1. */
void max11270_set_channel(max11270_dev_t *dev, uint8_t channel);

/** Drive GPIO3, which controls an external attenuator with an active-low
 *  enable input. enabled=true drives GPIO3 low (attenuator ON);
 *  enabled=false drives GPIO3 high (attenuator OFF). */
void max11270_set_attenuator(max11270_dev_t *dev, bool enabled);

/** Change PGA gain at runtime (1,2,4,8,16,32,64,128). Also updates
 *  dev->pga_gain so raw24->volts conversion stays correct afterward.
 *  Note: changing gain mid-stream requires the modulator to re-settle;
 *  expect a few stale/settling samples immediately after calling this. */
void max11270_set_gain(max11270_dev_t *dev, max11270_pga_gain_t gain);

/** Run the MAX11270's internal self-calibration (offset then full-scale).
 *  This corrects the chip's actual zero-scale and full-scale trim, which
 *  is NOT done automatically at power-on - an uncalibrated part can show
 *  a full-scale range far smaller than VREF would suggest, tripping AOR
 *  at a fraction of the expected input voltage.
 *  Blocks the calling task for up to ~500ms (polls MSTAT rather than a
 *  fixed delay); must be called from task context, never from an ISR.
 *  Automatically resumes continuous conversion afterward. Called once by
 *  max11270_init(); also safe to call again later (e.g. from a menu
 *  "recalibrate" action) since offset/gain drift with temperature/time. */
void max11270_self_calibrate(max11270_dev_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* MAX11270_H */