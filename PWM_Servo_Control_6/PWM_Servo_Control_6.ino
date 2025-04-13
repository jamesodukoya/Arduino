//Include the Liquid Crystal library in code
#include <LiquidCrystal.h>

//Initialize the library with the interface pin numbers used.
const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16,2); // Initialize LCD display

  // Use OCR1A - PB5 (pin11): Enable as an output:
  DDRB |= (1 << PB5);

  // COM1A1:0 (Bits 7 and 6) - Clear OC1A on Compare Match, set OC1A at BOTTOM (non-inverting mode) (The PWM output starts HIGH. It goes LOW when the counter matches OCR1A. Then resets to HIGH again at the start of the next cycle)
  // COM1B1:0, COM1C1:0 (Bits 5, 4, 3, 2) - OC1B and OC1C disconnected
  // WGM11:0 (Bits 1 and 0) - Fast PWM, Custom TOP (ICR1)
  TCCR1A = 0b10000010;

  // ICNC1 and ICES (Bits 7 and 6) - Input capture off, Bit 5 is empty
  // WGM13:2 (Bits 4 and 3) - Set TOP to ICR1
  // CS12:0 - Set prescaler to 8 (At default TOP (0xFFFF), period will be 32.768 ms)
  TCCR1B = 0b00011010;

  // Set TOP value for 20ms period
  ICR1 = 39999;

  // Set up for ultrasonic sensor
  DDRL = 0x01; // set PL0 (pin49) as output for ultrasonic trigger and PL1 (pin48) as input for ultrasonic echo

  // Set up Timer 3 for calculating distance
  TCCR3A = 0x00; // Set channels A, B, and C to normal port operation and normal wave generation mode.
  TCCR3B = 0b00000100; // Turn off input capture, set wave generation mode to normal, set prescale of 256.
}

void loop() {
  // Initialize arrays and variable to store scan data
  int angles[361];
  float distances[361];
  int index = 0;

  // Generate PWM signals to drive servo motor in a 180 degree pattern
  for(int angle=0;angle<181;angle++){ // Increment angles from 0 to 180
    float pwm_pulse = 999+4000*(float(angle)/180); // Calculate the corresponding value of OCR1A
    OCR1A = round(pwm_pulse); // Set the corresponding value of OCR1A for each angle
    float distance = detectObject(); // Call the function to calculate the distance of the closest object at that angle
    angles[index] = OCR1A; // Store the value of OCR1A
    distances[index] = distance; // Store the value of the distance measure at that angle
    printToLCD(distance); // Print the information to the LCD display
    delay(100); // Wait for 100 ms
    index++; // Increment the angle
  }
  publishScanResults(angles, distances); // Call function to point to the closest object from last scan
  for(int angle=180;angle>-1;angle--){
    float pwm_pulse = 999+4000*(float(angle)/180); // Calculate the corresponding value of OCR1A
    OCR1A = round(pwm_pulse); // Set the corresponding value of OCR1A for each angle
    float distance = detectObject(); // Call the function to calculate the distance of the closest object at that angle
    angles[index] = OCR1A; // Store the value of OCR1A
    distances[index] = distance; // Store the value of the distance measure at that angle
    printToLCD(distance); // Print the information to the LCD display
    delay(100); // Wait for 100 ms
    index++; // Increment the angle
  }
  publishScanResults(angles, distances); // Call function to point to the closest object from last scan
}

// Function to calculate the distance of the closest object using the ultrasonic sensor
float detectObject(){
  int time_start_bits = 0; // Will grab the start time (bit value) when the echo pin first turns HIGH
  int time_end_bits = 0; // Will grab the end time (bit value) when the echo pin turns LOW
  int duration_bits = 0; // Holds the duration (bit value) that the echo pin was on

  int trig_on_mask = 0x01, trig_off_mask = 0xFE; // Declare masks to turn ultrasonic trigger on and off
  int echo_mask = 0x02, echo_state = 0x02; // Declare masks to detect state of ultrasonic echo pin
  float duration_sec = 0.0; // Duration (seconds) that the echo pin was on
  const float ultrasonic_speed = 34300.0; // Ultrasonic speed in cm/s
  float proximity = 0.0; // Distance from ultrasonic sensor to nearest object

  // This procedure of turning off the trigger for 2 microsec, then on for 10 microsec, then back off is standard practice for this ultrasonic sensor.
  PORTL &= trig_off_mask; // Set ultrasonic trigger LOW
  delayMicroseconds(2); // Delay 2 microseconds
  PORTL |= trig_on_mask; // Set ultrasonic trigger HIGH
  delayMicroseconds(10); // Delay 10 microseconds
  PORTL &= trig_off_mask; // Set ultrasonic trigger LOW

  while((PINL & echo_mask) == 0x00){}; // Wait until the echo pin turns on
  time_start_bits = TCNT3; // Immediately after the echo pin turns on, set the start time (bit value) equal to T-COUNT 1.
  while((PINL & echo_mask) == echo_state){}; // Wait until echo pin turns back off
  time_end_bits = TCNT3; // Set the end time (bit value) equal to the new value of T-Count 1.
  duration_bits = time_end_bits - time_start_bits; // Calculate the signal duration (bit value) as the start minus the stop.
  duration_sec = float(duration_bits)*256.0/16000000.0; // Convert bit value into the signal duration in seconds.
  // Calculate distance from ultrasonic sensor to nearest object in centimeters.
  // Divide by two since the ultrasonic wave was transmitted and then reflected back.
  proximity = (ultrasonic_speed*duration_sec)/2; //proximity in cm
  return proximity;
}

void printToLCD(float dist){
  // Print the distance to the nearest object to the LCD screen.
  lcd.clear(); //clear LCD screen
  lcd.setCursor(0,0); //Set cursor to column 0, row 0
  lcd.print("Closest object's");
  lcd.setCursor(0,1); //Set cursor to column 0, row 1
  lcd.print(String(dist)+String(" cm away!")); // Print proximity value to LCD
}

void publishScanResults(int* angles, float* distances){ // Function to point to closest object from latest scan
  int indexofClosest = 0;
  for (int i = 1; i < 361; i++) { // Calculate least distance in the array of distance data
    if (distances[i] < distances[indexofClosest]) {
        indexofClosest = i;
    }
  }
  delay(500); // Wait for 500ms
  OCR1A = angles[indexofClosest];
  lcd.clear(); //clear LCD screen
  lcd.setCursor(0,0); //Set cursor to column 0, row 0
  lcd.print("There's your"); // Print message to LCD
  lcd.setCursor(0,1); //Set cursor to column 0, row 1
  lcd.print("intruder!!!!!");
  delay(3000);
}