
/***************************************************

  @file tca8418_keypad_interrupt.ino

  This is an example for the Adafruit TCA8418 Keypad Matrix / GPIO Expander Breakout

  Designed specifically to work with the Adafruit TCA8418 Keypad Matrix
  ----> https://www.adafruit.com/products/XXXX

  These Keypad Matrix use I2C to communicate, 2 pins are required to
  interface.
  The Keypad Matrix has an interrupt pin to provide fast detection
  of changes. This example shows the working of polling.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// TO BE VERIFIED
// 8.3.1.3 Key Event (FIFO) Reading

#include <Adafruit_TCA8418.h>

Adafruit_TCA8418 keypad;

//  typical Arduino UNO
const int IRQPIN = 3;

volatile bool TCA8418_event = false;

void TCA8418_irq()
{
  TCA8418_event = true;
}


void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println(__FILE__);

  if (! keypad.begin(TCA8418_DEFAULT_ADDR, &Wire)) {
    Serial.println("keypad not found, check wiring & pullups!");
    while (1);
  }

  //  configure the size of the keypad matrix.
  //  all other pins will be inputs
  keypad.matrix(8, 10);

  //  flush the internal buffer
  keypad.flush();

  //  install interrupt handler
  //  going LOW is interrupt
  pinMode(IRQPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), TCA8418_irq, CHANGE);

  //  enable interrupt mode
  keypad.enableInterrupts();
}


void loop()
{
  //  CHECKING THE STAT REGISTER WORKS
  static uint32_t last = 0;
  if (millis() - last > 1000)
  {
    last = millis();
    int x = keypad.readRegister(TCA8418_REG_INT_STAT);
    Serial.print("X:\t");
    Serial.println(x, HEX);

    if ((x & 0x01) == 0x01)
    {
      keypad.getEvent();
      keypad.writeRegister(TCA8418_REG_INT_STAT, 1);
    }
  }

  //  BUT THE INTERRUPTS DO NOT ARRIVE ON THE IRQ PIN.
  if (TCA8418_event == true)
  {
    TCA8418_event = false;
    //  datasheet page 15 - Table 1
    int k = keypad.getEvent();
    if (k & 0x80) Serial.print("PRESS\tR: ");
    else Serial.print("RELEASE\tR: ");
    k &= 0x7F;
    k--;
    Serial.print(k / 10);
    Serial.print("\tC: ");
    Serial.print(k % 10);
    Serial.println();
  }
  // other code here
  // delay(1000);
}
