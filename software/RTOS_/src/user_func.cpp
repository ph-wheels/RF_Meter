#include <Arduino.h>
#include "config.h"
#include "max11270.h"

static void show_cal_data(void)
{
    uint8_t raw_bytes[3];
    uint32_t cal_sts[4] = {0,0,0,0};

    max11270_read_reg(MAX11270_REG_SOC_SPI, raw_bytes, 3);
    cal_sts[0] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);
    max11270_read_reg(MAX11270_REG_SGC_SPI, raw_bytes, 3);
    cal_sts[1] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);
    max11270_read_reg(MAX11270_REG_SCOC_SPI, raw_bytes, 3);
    cal_sts[2] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);
    max11270_read_reg(MAX11270_REG_SCGC_SPI, raw_bytes, 3);
    cal_sts[3] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);

    Serial.printf("\nCalibration registers:\n");
    Serial.printf("        SOC      SGC         SCOC     SCGC\n");
    Serial.printf("Reg r/w 0x%03X S, 0x%03X S, 0x%03X C, 0x%03X C\n", cal_sts[0], cal_sts[1], cal_sts[2], cal_sts[3]);

    max11270_read_reg(MAX11270_REG_SOC_ADC, raw_bytes, 3);
    cal_sts[0] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);
    max11270_read_reg(MAX11270_REG_SGC_ADC, raw_bytes, 3);
    cal_sts[1] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);
    max11270_read_reg(MAX11270_REG_SCOC_ADC, raw_bytes, 3);
    cal_sts[2] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);
    max11270_read_reg(MAX11270_REG_SCGC_ADC, raw_bytes, 3);
    cal_sts[3] = ((uint32_t)raw_bytes[0] << 16) |
                  ((uint32_t)raw_bytes[1] << 8)  |
                  ((uint32_t)raw_bytes[2]);

    Serial.printf("Reg r/o 0x%03X S, 0x%03X S, 0x%03X C, 0x%03X C\n\n", cal_sts[0], cal_sts[1], cal_sts[2], cal_sts[3]);
}
