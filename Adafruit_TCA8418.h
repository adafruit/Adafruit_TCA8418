/*!
 *  @file Adafruit_TCA8418.h
 *
 * 	I2C Driver for the Adafruit TCA8418 Keypad Matrix / GPIO Expander Breakout
 *
 * 	This is a library for the Adafruit TCA8418 breakout:
 * 	https://www.adafruit.com/products/4918
 *
 * 	Adafruit invests time and resources providing this open source code,
 *  please support Adafruit and open-source hardware by purchasing products from
 * 	Adafruit!
 *
 *
 *	BSD license (see license.txt)
 */

#ifndef _ADAFRUIT_TCA8418_H
#define _ADAFRUIT_TCA8418_H

#include "Arduino.h"
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>

#define TCA8418_DEFAULT_ADDR 0x34 ///< The default I2C address for our breakout

enum {
  TCA8418_ROW0,
  TCA8418_ROW1,
  TCA8418_ROW2,
  TCA8418_ROW3,
  TCA8418_ROW4,
  TCA8418_ROW5,
  TCA8418_ROW6,
  TCA8418_ROW7,
  TCA8418_COL0,
  TCA8418_COL1,
  TCA8418_COL2,
  TCA8418_COL3,
  TCA8418_COL4,
  TCA8418_COL5,
  TCA8418_COL6,
  TCA8418_COL7,
  TCA8418_COL8,
  TCA8418_COL9
};

#define TCA8418_REG_GPIO_DIR1 0x23     ///< Register GPIO direciton (lowest)



/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the TCA8418 I2C GPIO expander
 */
class Adafruit_TCA8418 {
public:
  Adafruit_TCA8418();
  ~Adafruit_TCA8418();

  bool begin(uint8_t address = TCA8418_DEFAULT_ADDR, TwoWire *wire = &Wire);

  bool pinDirection(uint8_t pinnum, bool mode);

protected:
  Adafruit_I2CDevice *i2c_dev = NULL; ///< Pointer to I2C bus interface
};

#endif
