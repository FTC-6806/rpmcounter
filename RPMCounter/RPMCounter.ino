#include <FreqMeasure.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#define HERTZ_TO_RPM(x) x * 60

enum Mode {
  frequency,
  rotation
} mode;

enum Units {
  hz,
  rpm
} units;
  

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

void setup() {
  Serial.begin(57600);
  lcd.begin(16, 2);
  mode = frequency;
  units = hz;
  updateMode();
  FreqMeasure.begin();
}

double sum=0;
int count=0;

void loop() {
  if (FreqMeasure.available()) {
    // average several readings together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    if (count > 30) {
      float hertz = FreqMeasure.countToFrequency(sum / count);

      lcd.setCursor(0, 1);
      if (mode == frequency) {
        if (units == hz) {
          lcd.print(hertz);
          lcd.print(" Hz      ");
        }
      } 
      else if (mode == rotation) {
        if (units == rpm) {
          lcd.print(HERTZ_TO_RPM(hertz));
          lcd.print(" RPM     ");
        }
      }

      sum = 0;
      count = 0;
    }
  }

  uint8_t buttons = lcd.readButtons();
  if (buttons) {
    if (buttons & BUTTON_UP){
      mode = frequency;
      units = hz;
      updateMode();
    }
    if (buttons & BUTTON_DOWN) {
      mode = rotation;
      units = rpm;
      updateMode();
    }
  }
}

void updateMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (mode == frequency) {
    lcd.print("Frequency:");
  } 
  else if (mode == rotation) {
    lcd.print("Rotation:");
  }
}


