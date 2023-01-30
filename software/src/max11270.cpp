#include "Arduino.h"
#include "MAX11270.h"
#include "SPI.h"

/* with credits to: Lucas Etchezuri who created a library for max11214
 * which with some modifications could be addapted for max11270 (cheaper version)
 */

//#define max_debug

#define settings SPISettings(5000000, MSBFIRST, SPI_MODE0)
SPIClass * vspiMax = NULL;

MAX11270::MAX11270()
{
}

void MAX11270::writeRegister(uint8_t address, uint8_t value)
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_WRITE_REGISTER | (address << 1));
  vspiMax->transfer(value);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);
  #ifdef max_debug
    Serial.printf("Reg: %02x, Val: %02x\n", address, value);
  #endif
}

/* added as to be able to write spi based calibration registers */
void MAX11270::writeSpiRegister(uint8_t address, uint32_t value)
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_WRITE_REGISTER | (address << 1));
  uint8_t val1 = value >> 16;
  vspiMax->transfer(val1);
  uint8_t val2 = value >> 8;
  vspiMax->transfer(val2);
  vspiMax->transfer(value);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);
  #ifdef max_debug
    Serial.printf("Reg: %02x, Val: %02x\n", address, value);
  #endif
}

void MAX11270::execCal(uint8_t address, uint8_t value)
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_WRITE_REGISTER | (address << 1));
  vspiMax->transfer(value);
  delayMicroseconds(1); //00
  vspiMax->transfer(CMD_CALIBRATE);
  delayMicroseconds(250000);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);
  #ifdef max_debug
    Serial.printf("Reg: %02x, Val: %02x,\nCmd: %02x\n", address, value, CMD_CALIBRATE);
  #endif
}

uint8_t MAX11270::readRegister(uint8_t address)
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_READ_REGISTER | (address << 1));
  uint8_t data = vspiMax->transfer(SPI_MASTER_DUMMY);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);
  return data;
}

uint32_t MAX11270::readRegister24(uint8_t address)
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_READ_REGISTER | (address << 1));
  uint8_t data = vspiMax->transfer(SPI_MASTER_DUMMY);
  uint32_t val = data << 16;
  data = vspiMax->transfer(SPI_MASTER_DUMMY);
  uint32_t val2 = data << 8;
  uint32_t val3 = vspiMax->transfer(SPI_MASTER_DUMMY);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);
  return (val | val2 | val3);
  return 0;
}

uint32_t MAX11270::readRegister32(uint8_t address)
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_READ_REGISTER | (address << 1));
  uint32_t val = vspiMax->transfer32(SPI_MASTER_DUMMY32);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);
  return val;
}

void MAX11270::begin(uint8_t clk_pin, uint8_t miso_pin, uint8_t mosi_pin, uint8_t cs_pin, uint8_t drdy_pin)
{
  // get class object for internal usage
  vspiMax = new SPIClass(VSPI);
  // Set pins up
  MAX11270_CS_PIN = cs_pin;
  MAX11270_DRDY_PIN = drdy_pin;
  MAX11270_CLK_PIN = clk_pin;
  MAX11270_MISO_PIN = miso_pin;
  MAX11270_MOSI_PIN = mosi_pin;
  //digitalWrite(MAX11270_CS_PIN, HIGH); // Chip select high (inactive)
  pinMode(MAX11270_CS_PIN, OUTPUT);
  vspiMax->begin(MAX11270_CLK_PIN, MAX11270_MISO_PIN, MAX11270_MOSI_PIN, MAX11270_CS_PIN);
  vspiMax->beginTransaction(settings);
  // Configure DRDY as as input
  pinMode(MAX11270_DRDY_PIN, INPUT);
  vspiMax->endTransaction();
}

bool MAX11270::isDataReadyHard()
{
  if (digitalRead(MAX11270_DRDY_PIN) == HIGH)
  {
    return false;
  }
  return true;
}

void MAX11270::writeRegisterMasked(uint8_t address, uint8_t value, uint8_t mask)
{
  // Write the value to the register, applying the mask to touch only the necessary bits.
  // It does not perform the bit shift (shift), you have to pass the running value to the correct position.

  // Read content of the current register
  uint8_t register_contents = readRegister(address);

  // with the ~ Bitwise change the mask (1 remains in the bits that must not be touched and 0 in the bits to be modified)
  // An AND is performed with the current content of the record. "0" remains in the part to be modified
  register_contents = register_contents & ~mask;

  // an OR is performed with the value to be loaded into the register. Be careful, value must be in the correct position (shitf)
  register_contents = register_contents | value;

  // Rewrite the register
  writeRegister(address, register_contents);
}

bool MAX11270::isDataReadySoft()
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_READ_REGISTER | (REG_STAT << 1));
  uint16_t data = vspiMax->transfer16(SPI_MASTER_DUMMY);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);

  uint16_t x = (0x0001 & data);
  if (x != 1)
  {
    return false;
  }
  return true;
}

bool MAX11270::conversionInProgress()
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_READ_REGISTER | (REG_STAT << 1));
  uint16_t data = vspiMax->transfer16(SPI_MASTER_DUMMY);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);

  uint16_t x = (0x0002 & data);
  if (x > 0)
  {
    return true;
  }
  return false;
}

bool MAX11270::isPowerDown()
{
  digitalWrite(MAX11270_CS_PIN, LOW);
  vspiMax->beginTransaction(settings);
  delayMicroseconds(1);
  vspiMax->transfer(CMD_READ_REGISTER | (REG_STAT << 1));
  uint16_t data = vspiMax->transfer16(SPI_MASTER_DUMMY);
  delayMicroseconds(1);
  vspiMax->endTransaction();
  digitalWrite(MAX11270_CS_PIN, HIGH);

  uint16_t x = (0x0800 & data);
  if (x > 0)
  {
    return true;
  }
  return false;
}

bool MAX11270::setMode(uint8_t mode)
{
  if (mode == CONVERSION_MODE_CONT)
  {
    writeRegisterMasked(REG_CTRL1, B00000001, REG_MASK_MODE);
    return true;
  }
  else if (mode == CONVERSION_MODE_SINGLE)
  {
    writeRegisterMasked(REG_CTRL1, B00000010, REG_MASK_MODE);
    return true;
  }
  return false;
}

bool MAX11270::setDataFormat(uint8_t dataFormat)
{

  if (dataFormat == DATA_FORMAT_BINARY)
  {
    writeRegisterMasked(REG_CTRL1, B00000100, REG_MASK_DATA_FORMAT);
    return true;
  }
  else if (dataFormat == DATA_FORMAT_TWO_COMPLEMENT)
  {
    writeRegisterMasked(REG_CTRL1, B00000000, REG_MASK_DATA_FORMAT);
    return true;
  }
  return false;
}

bool MAX11270::setMeasuremode(uint8_t measureMode)
{

  if (measureMode == MEASURE_UNIPOLAR)
  {
    writeRegisterMasked(REG_CTRL1, B00001000, REG_MASK_MEASURE_MODE);
    return true;
  }
  else if (measureMode == MEASURE_BIPOLAR)
  {
    writeRegisterMasked(REG_CTRL1, B00000000, REG_MASK_MEASURE_MODE);
    return true;
  }
  return false;
}

bool MAX11270::setClocktype(uint8_t clockType)
{

  if (clockType == CLOCK_EXTERNAL)
  {
    writeRegisterMasked(REG_CTRL1, B10000000, REG_MASK_CLOCK_TYPE);
    return true;
  }
  else if (clockType == CLOCK_INTERNAL)
  {
    writeRegisterMasked(REG_CTRL1, B00000000, REG_MASK_CLOCK_TYPE);
    return true;
  }
  return false;
}

bool MAX11270::setPgaEnable(bool pgaEnable)
{
  if (pgaEnable)
  {
    writeRegisterMasked(REG_CTRL2, B00001000, REG_MASK_PGA_ENABLE);
  }
  else
  {
    writeRegisterMasked(REG_CTRL2, B00000000, REG_MASK_PGA_ENABLE);
  }
  return true;
}

bool MAX11270::setPgaGain(uint8_t pgaGain)
{
  if ((0 <= pgaGain) and (pgaGain < 8))
  {
    writeRegisterMasked(REG_CTRL2, pgaGain, REG_MASK_PGA_GAIN);
    return true;
  }
  return false;
}

bool MAX11270::setFilter(uint8_t filter)
{

  if (filter == FILTER_SINC)
  {
    writeRegisterMasked(REG_CTRL3, B00000000, REG_MASK_FILTER);
    return true;
  }
  else if (filter == FILTER_FIR)
  {
    writeRegisterMasked(REG_CTRL3, B00000010, REG_MASK_FILTER);
    return true;
  }
  else if (filter == FILTER_FIR_IIR)
  {
    writeRegisterMasked(REG_CTRL3, B00000011, REG_MASK_FILTER);
    return true;
  }
  return false;
}

bool MAX11270::setDataMode(uint8_t dataMode)
{

  if (dataMode == DATA_MODE_24BITS)
  {
    writeRegisterMasked(REG_CTRL3, B00000000, REG_MASK_DATA_MODE);
    return true;
  }
  else if (dataMode == DATA_MODE_32BITS)
  {
    writeRegisterMasked(REG_CTRL3, B00001000, REG_MASK_DATA_MODE);
    return true;
  }

  return false;
}

uint8_t MAX11270::getDataMode()
{
  uint8_t dataMode = readRegister(REG_CTRL3) & REG_MASK_DATA_MODE;

  if (dataMode == DATA_MODE_24BITS)
  {
    return DATA_MODE_24BITS;
  }
  return DATA_MODE_32BITS;
}

bool MAX11270::startConversion(uint8_t dataRate)
{
  if ((dataRate >= 0) and (dataRate < 16))
  {
    digitalWrite(MAX11270_CS_PIN, LOW);
    vspiMax->beginTransaction(settings);
    delayMicroseconds(1);
    vspiMax->transfer(CMD_CONVERSION | dataRate);
    delayMicroseconds(1);
    vspiMax->endTransaction();
    digitalWrite(MAX11270_CS_PIN, HIGH);
    return true;
  }
  return false;
}

uint32_t MAX11270::readADC(void)
{
  return (readRegister24(REG_DATA));
}

uint32_t MAX11270::readADC32(void)
{
  return (readRegister32(REG_DATA));
}

bool MAX11270::setAnalogInputBuffer(bool inputBuffer)
{
  if (inputBuffer)
  {
    writeRegisterMasked(REG_CTRL2, B00100000, REG_MASK_INPUT_BUFFER);
  }
  else
  {
    writeRegisterMasked(REG_CTRL2, B00000000, REG_MASK_INPUT_BUFFER);
  }
  return true;
}

bool MAX11270::setSyncMode(uint8_t syncMode)
{
  if (syncMode == SYNC_CONTINUOUS)
  {
    writeRegisterMasked(REG_CTRL1, B01000000, REG_MASK_SYNC_MODE);
  }
  else
  {
    writeRegisterMasked(REG_CTRL1, B00000000, REG_MASK_SYNC_MODE);
  }
  return true;
}

bool MAX11270::setModulatorSync(bool Modsync)
{
  if (Modsync)
  {
    writeRegisterMasked(REG_CTRL3, B00100000, REG_MASK_MOD_SYNC);
  }
  else
  {
    writeRegisterMasked(REG_CTRL3, B00000000, REG_MASK_MOD_SYNC);
  }
  return true;
}

bool MAX11270::setConfDIO(uint8_t dio, uint8_t mode)
{
  if (dio == 1)
  {
    if (mode == DIO_OUTPUT)
      writeRegisterMasked(REG_CTRL4, B00010000, REG_MASK_CONF_DIO1);
    else
      writeRegisterMasked(REG_CTRL4, B00000000, REG_MASK_CONF_DIO1);
  }

  if (dio == 2)
  {
    if (mode == DIO_OUTPUT)
      writeRegisterMasked(REG_CTRL4, B00100000, REG_MASK_CONF_DIO2);
    else
      writeRegisterMasked(REG_CTRL4, B00000000, REG_MASK_CONF_DIO2);
  }

  if (dio == 3)
  {
    if (mode == DIO_OUTPUT)
      writeRegisterMasked(REG_CTRL4, B01000000, REG_MASK_CONF_DIO3);
    else
      writeRegisterMasked(REG_CTRL4, B00000000, REG_MASK_CONF_DIO3);
  }
  return true;
}

bool MAX11270::writeBinDIO(uint8_t mask, uint8_t data) {

  writeRegister(REG_CTRL4, mask | data);
  //Serial.printf("mask %x, data %x, result %x\r\n", mask, data, mask | data);
  return true;
}

bool MAX11270::writeDIO(uint8_t dio, bool data)
{
  if (dio == 1)
  {
    if (data == true)
      writeRegisterMasked(REG_CTRL4, B00000001, REG_MASK_CONF_DIO1);
    else
      writeRegisterMasked(REG_CTRL4, B00000000, REG_MASK_CONF_DIO1);
  }

  if (dio == 2)
  {
    if (data == true)
      writeRegisterMasked(REG_CTRL4, B00000010, REG_MASK_CONF_DIO2);
    else
      writeRegisterMasked(REG_CTRL4, B00000000, REG_MASK_CONF_DIO2);
  }

  if (dio == 3)
  {
    if (data == true)
      writeRegisterMasked(REG_CTRL4, B00000100, REG_MASK_CONF_DIO3);
    else
      writeRegisterMasked(REG_CTRL4, B00000000, REG_MASK_CONF_DIO3);
  }
  return true;
}

bool MAX11270::readDIO(uint8_t dio)
{
  uint8_t reg = readRegister(REG_CTRL4);
  uint8_t res = 0;

  if (dio == 1)
    res = (reg & B00000001);
  if (dio == 2)
    res = (reg & B00000010);
  if (dio == 3)
    res = (reg & B00000100);
  if (res == 0)
    return 0;
  else
    return 1;
}

