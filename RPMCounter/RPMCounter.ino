#include <FreqCounter.h>

#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() {
  Serial.begin(57600);
  lcd.begin(16, 2); // Set up the LCD
  lcd.print("Frequency:"); // Print out a headline on the LCD
}

long int frq;
long int lfrq;
void loop() {
  FreqCounter::f_comp= 8;             // Set compensation to 12
  FreqCounter::start(100);            // Start counting with gatetime of 100ms
  while (FreqCounter::f_ready == 0)         // wait until counter ready
  frq=FreqCounter::f_freq;            // read result
  
  if (lfrq != frq) {
    lcd.setCursor(0, 1); // Set the cursor to column 0, line 1
    //lcd.print("                  "); // Yeah. Not how it's supposed to be done :P
    lcd.setCursor(0, 1); // Set the cursor to column 0, line 1
    lcd.print(String(frq) + "    Hz    "); // Print the hertz
  }
  
  lfrq = frq;  
  delay(20);
}


