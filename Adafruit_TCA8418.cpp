/*!
 *  @file Adafruit_TCA8418.cpp
 *
 *  @mainpage I2C Driver for the Adafruit TCA8418 Keypad Matrix / GPIO Expander Breakout
 *
 *  @section intro_sec Introduction
 *
 * 	I2C Driver for the Adafruit TCA8418 Keypad Matrix / GPIO Expander Breakout
 *
 * 	This is a library for the Adafruit TCA8418 breakout:
 * 	https://www.adafruit.com/product/4918
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *  @section dependencies Dependencies
 *  This library depends on the Adafruit BusIO library
 *
 *  @section author Author
 *
 *  Limor Fried (Adafruit Industries)
 *
 * 	@section license License
 *
 * 	BSD (see license.txt)
 *
 * 	@section  HISTORY
 *
 *     v1.0 - First release
 */

#include "Arduino.h"

#include "Adafruit_TCA8418.h"

/*!
 *    @brief  Instantiates a new TCA8418 class
 */
Adafruit_TCA8418::Adafruit_TCA8418(void) {}

Adafruit_TCA8418::~Adafruit_TCA8418(void) {}

/*!
 *    @brief  Sets up the hardware and initializes I2C
 *    @param  addr The I2C address for the expander
 *    @param  wire
 *            The Wire object to be used for I2C connections.
 *    @return True if initialization was successful, otherwise false.
 */
bool Adafruit_TCA8418::begin(uint8_t addr, TwoWire *wire) {
  if (i2c_dev) {
    delete i2c_dev; // remove old interface
  }

  i2c_dev = new Adafruit_I2CDevice(addr, wire);

  if (!i2c_dev->begin()) {
    return false;
  }


  return true;
}

/*!
 *    @brief  Sets GPIO data direction for a pin
 *    @param  pinnum Pin name between TCA8418_ROW0 and TCA8418_COL9
 *    @param  mode INPUT for input GPIO, OUTPUT for output!
 *    @return True I2C write command was acknowledged
 */
bool Adafruit_TCA8418::pinDirection(uint8_t pinnum, bool mode) {
  if (pinnum > TCA8418_COL9) {
    return false;
  }

  uint8_t reg = TCA8418_REG_GPIO_DIR1 + pinnum / 8;
  uint8_t bit = pinnum % 8;

  Adafruit_I2CRegister gpiodirreg = Adafruit_I2CRegister(i2c_dev, reg);
  Adafruit_I2CRegisterBits dirbit =
      Adafruit_I2CRegisterBits(&gpiodirreg, 1, bit); // # bits, bit_shift

  return dirbit.write(mode);
}

/*!
 *    @brief  Sets GPIO data direction for a pin
 *    @param  pinnum Pin name between TCA8418_ROW0 and TCA8418_COL9
 *    @return True I2C write command was acknowledged
 */
bool Adafruit_TCA8418::pinDirection(uint8_t pinnum, bool mode) {
  if (pinnum > TCA8418_COL9) {
    return false;
  }
  uint8_t reg = TCA8418_REG_GPIO_DIR1 + pinnum / 8;
  uint8_t bit = pinnum % 8;

  Adafruit_I2CRegister gpiodirreg = Adafruit_I2CRegister(i2c_dev, reg);
  Adafruit_I2CRegisterBits dirbit =
      Adafruit_I2CRegisterBits(&gpiodirreg, 1, bit); // # bits, bit_shift

  return dirbit.write(mode);
}
