/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 https://docs.arduino.cc/learn/electronics/lcd-displays

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  DDRA = 0b11111111; // set all PORTA as outputs
  DDRC = 0b11111111;
}

void loop() {
  // print a welcome message
  lcd.print("Welcome!");
  delay(1000); // delay 1000 ms
  lcd.setCursor(1, 1);
  lcd.print("Time for eggs!");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Ingredients");
  delay(1000); // delay 1000 ms
  lcd.setCursor(0, 1);
  lcd.print("Cooking oil");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Onions");
  delay(1000); // delay 1000 ms
  lcd.setCursor(0, 1);
  lcd.print("Fresh tomatoes");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Bell pepper");
  delay(1000); // delay 1000 ms
  lcd.setCursor(0, 1);
  lcd.print("Of course, eggs!");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Now, let's go!");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Pour some oil");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("in a dry pan");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Allow to fry for");
  delay(1000); // delay 1000 ms
  lcd.setCursor(0, 1);
  lcd.print("about 10 secs");
  PORTC = 0b00111111;
  int digit[10] = {0b01101111, 0b01111111, 0b00000111, 0b01111101, 0b01101101, 0b01100110, 0b01001111, 0b01011011, 0b00000110, 0b00111111};
    for (int i=0; i<10; i++){
      PORTA = digit[i];
      delay(1000);
    }
  delay(1000);
  // delay(3000);
  lcd.clear(); // Clears the display
  lcd.print("Add all chopped");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("veggies and stir");
  delay(3000);
  lcd.clear(); // Clears the display
  lcd.print("Crack the eggs");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("And pour in pan");
  delay(3000);
  lcd.clear(); // Clears the display
  lcd.print("Leave to fry");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Till satisfied");
  // PORTC = 0b01111111;
  // int digit[10] = {0b01101111, 0b01111111, 0b00000111, 0b01111101, 0b01101101, 0b01100110, 0b01001111, 0b01011011, 0b00000110, 0b00111111};
    for (int i=0; i<10; i++){
      PORTA = digit[i];
      delay(1000);
    }
  delay(500);
  lcd.clear(); // Clears the display
  lcd.print("That's it!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("You're done!");
  delay(5000);
  lcd.clear(); // Clears the display
}