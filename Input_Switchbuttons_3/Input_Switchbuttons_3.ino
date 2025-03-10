
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 300;    // the debounce time; increase if the output flickers

// include the library code:
#include <LiquidCrystal.h>
using namespace std;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  DDRA = 0x00; // PORTA all inputs
  PORTA = 0b10001111; // set pull up resistors on PA0, PA1, PA2, and PA3

  lcd.begin(16, 2);

  Serial.begin(9600); // init serial print
  Serial.println("Serial communication is ready");
}

void loop() {
  int mask = 0b11110000;
  char placeHolder[4] = {"s"};

  lcd.clear(); // Clears the display
  lcd.print("Welcome!");
  delay(1000); // delay 1000 ms
  lcd.setCursor(1, 1);
  lcd.print("Time for eggs!");
  delay(1000); // delay 1000 ms
  lcd.clear(); // Clears the display
  lcd.print("Recipe locked");
  delay(1000); // delay 1000 ms
  lcd.setCursor(1, 1);
  lcd.print("Enter PIN code!");
  delay(1000); // delay 1000 ms

  int pinCode[4];

  for (int i=0; i<4; i++){
    while((PINA | mask) == 0b11111111){}; // look to see if SW0, SW1, SW2, or SW3 are pressed
    
    // Implement debouncing logic
    if ( (millis() - lastDebounceTime) > debounceDelay) { // check if 300ms (debounceDelay time) has passed since a pushbutton was toggled
      lcd.clear(); // Clears the display
      lcd.setCursor(0, 1);
      lcd.print(placeHolder);
      placeHolder[i+1] = "*";
      pinCode[i] = (PINA);
      // Serial.println(o);
      // for 
      Serial.println(pinCode[i]);
      lastDebounceTime = millis();
    }
    delay(300);
  }
  if (pinCode[0] == 142 && pinCode[1] == 141 && pinCode[2] == 139 && pinCode[3] == 135){ //Check if code entered is 1234
    lcd.clear(); // Clears the display
    lcd.print("Awesome!");
    delay(1000);
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
  delay(3000);
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
  delay(3000);
  lcd.clear(); // Clears the display
  lcd.print("That's it!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("You're done!");
  delay(5000);
  } else {
    lcd.clear(); // Clears the display
    lcd.print("Wrong code");
    delay(1000); // delay 1000 ms
    lcd.setCursor(1, 1);
    lcd.print("Start over!");
    delay(1000);
  }
}