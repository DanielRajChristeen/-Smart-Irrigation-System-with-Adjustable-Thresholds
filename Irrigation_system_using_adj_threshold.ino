#include <LiquidCrystal.h>

uint8_t Moisture_tr_val, Moisture_val, Tank_tr_val, Tank_val;
float Temperature_tr_val, Temperature_val;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

float readTemperature(int pin) {
  return (-40 + 0.488155 * (analogRead(pin) - 20));
}

uint8_t readMoistureOrTank(int pin) {
  return map(analogRead(pin), 0, 1023, 0, 100);
}

void setup() {
  lcd.begin(20, 4);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  Moisture_tr_val = readMoistureOrTank(A0);
  Temperature_tr_val = readTemperature(A1);
  Tank_tr_val = readMoistureOrTank(A2);

  lcd.print("IRRIGATION SYSTEM   WITH ADJ-THRESHOLDS");
  delay(200);
  lcd.clear();
  lcd.print("Set Threshold Values");
  delay(200);
  Moisture_tr_val = readMoistureOrTank(A0);
  Temperature_tr_val = readTemperature(A1);
  Tank_tr_val = readMoistureOrTank(A2);
  lcd.clear();
}

void loop() {
  Moisture_val = readMoistureOrTank(A3);
  Temperature_val = readTemperature(A4);
  Tank_val = readMoistureOrTank(A5);

  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.print(Moisture_val);
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(Temperature_val);
  lcd.setCursor(0, 2);
  lcd.print("Tank:");
  lcd.print(Tank_val);

  if (Moisture_val <= Moisture_tr_val) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture:");
    lcd.print(Moisture_val);
    lcd.setCursor(0, 1);
    lcd.print("Low Moisture");
    }
  if (Temperature_val > Temperature_tr_val) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(Temperature_val);
    lcd.setCursor(0, 1);
    lcd.print("High Temp");
    }
  if (Tank_val < Tank_tr_val) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(Temperature_val);
    lcd.setCursor(0, 1);
    lcd.print("Empty Tank");
    }

  delay(100);
}