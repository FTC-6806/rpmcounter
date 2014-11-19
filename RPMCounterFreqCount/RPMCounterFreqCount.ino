/* FreqCount - Example with LCD output
 * http://www.pjrc.com/teensy/td_libs_FreqCount.html
 *
 * This example code is in the public domain.
 */
#include <FreqCount.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


void setup() {
  Serial.begin(57600);
  lcd.begin(16, 2);
  lcd.print("Freq:");
  FreqCount.begin(1000);
}

void loop() {
  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();
    lcd.setCursor(0, 1);
    lcd.print(count);
    lcd.print(" Hz      ");
  }
}

