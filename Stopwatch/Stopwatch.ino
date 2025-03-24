long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 300;    // the debounce time; increase if the output flickers

int mask = 0b11110000; // declare mask to check state of SW0, SW1, SW2, and SW3


void setup() {
  // put your setup code here, to run once:
  DDRA = 0b11111111; // set all PORTA (print number) as outputs
  DDRC = 0b11111111; // set all PORTC (digit selector) as outputs

  DDRL = 0x00; // PORTL all inputs
  PORTL = 0b00001111; // set pull up resistors on PA0, PA1, PA2, and PA3

  TCCR1A = 0x00; // Set channels A, B, and C to normal port operation and normal wave generation mode.
  TCCR1B = 0b00000101; // Turn off input capture, set wave generation mode to normal, set prescale of 1024.

  Serial.begin(9600); // init serial print
  Serial.println("Serial communication is ready");
}

// Digit array from 0 to 9
int digit[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};


void loop() {
  // put your main code here, to run repeatedly:
  PORTC = 0b01110000; // turn on only digit 1

  while((PINL | mask) != 0b11111110){}; // Check if SW0 has been pressed

  if ( (millis() - lastDebounceTime) > debounceDelay) { // Fix debounce logic
    count(); // call Counter function
    lastDebounceTime = millis(); // assign present time to lastDebounceTime
  }
}

// Function to implement Counter
void count(){
  for (int i=0; i<10; i++){ // Count from 0 to 9
    PORTA = digit[i]; // display current number
    // delay(3000);
    TCNT1=0; // clear the timer
    while(TCNT1 != 46875 | (PINL | mask) == 0b11111101){ // wait for 3 seconds (16,000,000/1024 * 3) or detect SW1 click
      if ((PINL | mask) == 0b11111101){ // Check if SW1 has been pressed
        if ( (millis() - lastDebounceTime) > debounceDelay) { // debounce logic
          PORTA = 0x00; // clear LED
          loop(); // return to initial state of the function
          lastDebounceTime = millis();
        }
      }
    } 
  }
  count(); // start counter all over
}