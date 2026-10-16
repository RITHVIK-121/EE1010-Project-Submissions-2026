#include <LiquidCrystal.h>
#include <math.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;

// Arduino voltage reference
const float VREF = 5.000;

// Calibration coefficients
const float A = 116.3865;
const float B = -825.3788;
const float C = 1379.8833;

// Temperature correction
const float TEMP_OFFSET = -5.0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("PT100 Thermometer");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Average 20 ADC readings
  long adcSum = 0;

  for (int i = 0; i < 20; i++) {
    adcSum += analogRead(sensorPin);
    delay(10);
  }

  float adcValue = adcSum / 20.0;

  // Convert ADC to voltage
  float voltage = adcValue * VREF / 1023.0;

  // Calculate temperature
  float temperature =
      A * voltage * voltage +
      B * voltage +
      C;

  // Apply correction
  temperature += TEMP_OFFSET;

  // Display voltage
  lcd.setCursor(0, 0);
  lcd.print("Voltage:");
  lcd.print(voltage, 3);
  lcd.print("V   ");

  // Display temperature
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.write(byte(223));
  lcd.print("C     ");

  delay(500);
}
