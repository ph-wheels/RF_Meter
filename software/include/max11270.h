#ifndef MAX11270_h
#define MAX11270_h

#include "Arduino.h"

// credits to: LucasEtchezuri who created a library for max11214
// https://github.com/LucasEtchezuri/Arduino-MAX11214

// Conversion modes
#define CONVERSION_MODE_CONT 0
#define CONVERSION_MODE_SINGLE 1

// Data Format
#define DATA_FORMAT_TWO_COMPLEMENT 0
#define DATA_FORMAT_BINARY 1

// Measure Mode
#define MEASURE_UNIPOLAR 1
#define MEASURE_BIPOLAR 0

// Clock Type
#define CLOCK_EXTERNAL 1
#define CLOCK_INTERNAL 0

// PGA Gain
#define PGA_GAIN_1          0
#define PGA_GAIN_2          1
#define PGA_GAIN_4          2
#define PGA_GAIN_8          3
#define PGA_GAIN_16         4
#define PGA_GAIN_32         5
#define PGA_GAIN_64         6
#define PGA_GAIN_128        7

// Input Filter
#define FILTER_SINC        0
#define FILTER_FIR         2
#define FILTER_FIR_IIR     3

// Data Mode
#define DATA_MODE_24BITS   0
#define DATA_MODE_32BITS   1

// Data Rate
#define DATA_RATE_0     0
#define DATA_RATE_1     1
#define DATA_RATE_2     2
#define DATA_RATE_3     3
#define DATA_RATE_4     4
#define DATA_RATE_5     5
#define DATA_RATE_6     6
#define DATA_RATE_7     7
#define DATA_RATE_8     8
#define DATA_RATE_9     9
#define DATA_RATE_10   10
#define DATA_RATE_11   11
#define DATA_RATE_12   12
#define DATA_RATE_13   13
#define DATA_RATE_14   14
#define DATA_RATE_15   15

// Sync Mpdes
#define SYNC_CONTINUOUS 1
#define SYNC_PULSE      0

// DIO Config Mode
#define DIO_OUTPUT  1
#define DIO_INPUT  0


// Commands
#define CMD_READ_REGISTER   0xC1  // Register Access Mode  (dec=193)
#define CMD_WRITE_REGISTER  0xC0 // Register Access Mode  (dec=192)
#define CMD_CONVERSION      0x80 // Register Access Mode  (dec=192)
#define CMD_CALIBRATE       0xA0

// Registers MAPS
#define REG_STAT 0x00
#define REG_CTRL1 0x01
#define REG_CTRL2 0x02
#define REG_CTRL3 0x03
#define REG_CTRL4 0x04
#define REG_CTRL5 0x05
#define REG_DATA  0x06
#define REG_SOC_SPI 0x07
#define REG_SGC_SPI 0x08
#define REG_SCOC_SPI 0x09
#define REG_SCGC_SPI 0x0A
#define REG_HPF 0x0B
#define REG_RAM 0x0C
#define REG_SYNC_SPI 0x0D
#define REG_SOC_ADC 0x15
#define REG_SGC_ADC 0x16
#define REG_SCOC_ADC 0x17
#define REG_SCGC_ADC 0x18

// Mask Register CTRL1
#define REG_MASK_MODE         0x03
#define REG_MASK_DATA_FORMAT  0x04
#define REG_MASK_MEASURE_MODE 0x08
#define REG_MASK_SYNC_MODE    0x40
#define REG_MASK_CLOCK_TYPE   0x80



// Mask Register CTRL2
#define REG_MASK_PGA_GAIN 0x07
#define REG_MASK_PGA_ENABLE 0x08
#define REG_MASK_INPUT_BUFFER 0x20


// Mask Register CTRL3
#define REG_MASK_FILTER     0x03
#define REG_MASK_DATA_MODE  0x08
#define REG_MASK_MOD_SYNC   0x20

// Mask Register CTRL4
#define REG_MASK_DIO1       0x01
#define REG_MASK_DIO2       0x02
#define REG_MASK_DIO3       0x04
#define REG_MASK_CONF_DIO1  0x10
#define REG_MASK_CONF_DIO2  0x20
#define REG_MASK_CONF_DIO3  0x40

#define REG_MASK_DATA_MODE  0x08
#define REG_MASK_MOD_SYNC   0x20

#define SPI_MASTER_DUMMY 0xFF
#define SPI_MASTER_DUMMY16 0xFFFF
#define SPI_MASTER_DUMMY32 0xFFFFFFFF


class MAX11270
{
public:
  MAX11270();
  uint8_t MAX11270_CS_PIN;
  uint8_t MAX11270_DRDY_PIN;
  uint8_t MAX11270_CLK_PIN;
  uint8_t MAX11270_MISO_PIN;
  uint8_t MAX11270_MOSI_PIN;

  void writeRegister(uint8_t address, uint8_t value);
  void execCal(uint8_t address, uint8_t value);
  uint8_t readRegister(uint8_t address);
  uint32_t readRegister24(uint8_t address);
  uint32_t readRegister32(uint8_t address);
  void begin(uint8_t clk_pin, uint8_t miso_pin, uint8_t mosi_pin, uint8_t cs_pin, uint8_t drdy_pin);
  bool isDataReadyHard(void);
  void writeRegisterMasked(uint8_t address, uint8_t value, uint8_t mask);
  bool isDataReadySoft(void);
  bool conversionInProgress(void);
  bool isPowerDown(void);
  bool setMode(uint8_t mode);
  bool setDataFormat(uint8_t dataFormat);
  bool setMeasuremode(uint8_t measureMode);
  bool setClocktype(uint8_t clockType);
  bool setPgaEnable(bool pgaEnable);
  bool setPgaGain(uint8_t pgaGain);
  bool setFilter(uint8_t filter);
  bool setDataMode(uint8_t dataMode);
  uint8_t getDataMode();
  bool startConversion(uint8_t dataRate);
  uint32_t readADC(void);
  bool setAnalogInputBuffer(bool inputBuffer);
  bool setSyncMode(uint8_t syncMode);
  uint32_t readADC32(void);
  bool setModulatorSync(bool Modsync);
  bool setConfDIO(uint8_t dio, uint8_t mode);
  bool writeDIO(uint8_t dio, bool data);
  bool writeBinDIO(uint8_t mask, uint8_t data);
  bool readDIO(uint8_t dio);
  void writeSpiRegister(uint8_t address, uint32_t value);
};
#endif
