
/***************************************************

  @file tca8418_test_interrupt.ino
  
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
const int IRQPIN = 2;

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
  keypad.matrix(3, 3);

  //  flush the internal buffer
  keypad.flush();

  //  install interrupt handler
  //  going LOW is interrupt
  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), TCA8418_irq, FALLING);

  //  enable interrupt mode
  keypad.enableInterrupts();
}


void loop()
{
  if (TCA8418_event)
  {
    TCA8418_event = false;
    int k = keypad.getEvent();
    Serial.println(k, HEX);
  }
  // other code here
  delay(1000);
}
