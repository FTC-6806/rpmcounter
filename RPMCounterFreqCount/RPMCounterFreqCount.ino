#include <FreqCount.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#define HERTZ_TO_RPM(x) x * 60

enum Mode {
  frequency,
  rpm
} mode;

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup() {
  Serial.begin(57600);
  lcd.begin(16, 2);
  mode = frequency;
  updateMode();
  FreqCount.begin(1000);
}

void loop() {
  if (FreqCount.available()) {
    unsigned long hertz = FreqCount.read();
    lcd.setCursor(0, 1);
    if (mode == frequency) {
      lcd.print(hertz);
      lcd.print(" Hz      ");
    } else if (mode == rpm) {
      lcd.print(HERTZ_TO_RPM(hertz));
      lcd.print(" RPM     ");
    }
  }
  
  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    if (buttons & BUTTON_UP){
      mode = frequency;
      updateMode();
    }
    if (buttons & BUTTON_DOWN) {
      mode = rpm;
      updateMode();
    }
  }
}

void updateMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (mode == frequency) {
    lcd.print("Frequency:");
  } else if (mode == rpm) {
    lcd.print("RPM:");
  }
}
