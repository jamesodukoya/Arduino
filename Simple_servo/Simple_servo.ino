#include <Servo.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo Servo1;
int servoPin = 22;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Servo1.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  int angle = -15;
  for (int i=0; i<13; i++){
    angle += 15;
    Servo1.write(angle);
    lcd.clear(); // Clears the display
    lcd.print("Servo angle is");
    lcd.setCursor(0, 1);
    lcd.print(String(angle) + String(" degrees!"));
    delay(2000);
  }
}
