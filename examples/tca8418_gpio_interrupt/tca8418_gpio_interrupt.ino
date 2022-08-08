
/***************************************************

  @file tca8418_gpio_interrupt.ino

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

Adafruit_TCA8418 tio;

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

  if (! tio.begin(TCA8418_DEFAULT_ADDR, &Wire)) {
    Serial.println("TCA8418 not found, check wiring & pull ups!");
    while (1);
  }

  //  SET INPUT MODE
  for (int pin = 0; pin < 18; pin++)
  {
    tio.pinMode(pin, INPUT_PULLUP);
    tio.pinIRQMode(pin, FALLING);
  }

  //  install interrupt handler on processor
  //  going LOW is interrupt
  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), TCA8418_irq, FALLING);

  //  enable interrupt mode
  tio.enableInterrupts();
}


void loop()
{
  //  CHECKING THE STAT REGISTER WORKS
  static uint32_t last = 0;
  if (millis() - last > 1000)
  {
    last = millis();
    int x = tio.readRegister(TCA8418_REG_INT_STAT);
    Serial.print("X:\t");
    Serial.println(x, HEX);

    if ((x & 0x02) == 0x02)
    {
      tio.writeRegister(TCA8418_REG_INT_STAT, 2);  // does not reset ..
      tio.writeRegister(TCA8418_REG_INT_STAT, 1);  // does not reset ..
    }
  }


  //  BUT THE INTERRUPTS DO NOT ARRIVE ON THE IRQ PIN.
  if (TCA8418_event == true)
  {
    TCA8418_event = false;
    //  SHOW PIN STATUS
    for (int pin = 0; pin < 18; pin++)
    {
      Serial.print(tio.digitalRead(pin));
      Serial.print(' ');
    }
    Serial.println();
  }
  // other code here
  // delay(1000);
}
