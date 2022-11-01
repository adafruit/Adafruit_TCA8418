/*!
 *  @file Adafruit_TCA8418.h
 *
 * 	I2C Driver for the Adafruit TCA8418 Keypad Matrix / GPIO Expander
 *Breakout
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
#include <Adafruit_TCA8418_registers.h>

#define TCA8418_DEFAULT_ADDR 0x34 ///< The default I2C address for our breakout

enum {
  TCA8418_ROW0, ///< Row 0
  TCA8418_ROW1, ///< Row 1
  TCA8418_ROW2, ///< Row 2
  TCA8418_ROW3, ///< Row 3
  TCA8418_ROW4, ///< Row 4
  TCA8418_ROW5, ///< Row 5
  TCA8418_ROW6, ///< Row 6
  TCA8418_ROW7, ///< Row 7
  TCA8418_COL0, ///< Column 0
  TCA8418_COL1, ///< Column 1
  TCA8418_COL2, ///< Column 2
  TCA8418_COL3, ///< Column 3
  TCA8418_COL4, ///< Column 4
  TCA8418_COL5, ///< Column 5
  TCA8418_COL6, ///< Column 6
  TCA8418_COL7, ///< Column 7
  TCA8418_COL8, ///< Column 8
  TCA8418_COL9  ///< Column 9
};

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            the TCA8418 I2C GPIO expander
 */
class Adafruit_TCA8418 {
public:
  Adafruit_TCA8418();
  ~Adafruit_TCA8418();

  //  initialize the TCA8418
  bool begin(uint8_t address = TCA8418_DEFAULT_ADDR, TwoWire *wire = &Wire);

  //  KEY EVENTS
  //  configure the size of the keypad.
  //  all other rows and columns are set as inputs.
  bool matrix(uint8_t rows, uint8_t columns);

  //  key events available in the internal FIFO buffer
  uint8_t available();

  //  get one event from the FIFO buffer
  //  bit 7 indicates  press = 0  or  release == 1 (mask 0x80)
  uint8_t getEvent();

  //  flush all events in the FIFO buffer + GPIO events
  uint8_t flush();

  //  GPIO
  uint8_t digitalRead(uint8_t pinnum);
  bool digitalWrite(uint8_t pinnum, uint8_t level);
  bool pinMode(uint8_t pinnum, uint8_t mode);
  bool pinIRQMode(uint8_t pinnum, uint8_t mode); // MODE  FALLING or RISING

  //  CONFIGURATION
  //  enable / disable interrupts for matrix and GPI pins
  void enableInterrupts();
  void disableInterrupts();

  //  ignore key events when FIFO buffer is full or not.
  void enableMatrixOverflow();
  void disableMatrixOverflow();

  //  debounce keys.
  void enableDebounce();
  void disableDebounce();

  // for expert mode
  uint8_t readRegister(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t value);

protected:
  Adafruit_I2CDevice *i2c_dev = NULL; ///< Pointer to I2C bus interface
};

#endif
