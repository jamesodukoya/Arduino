// Lab 5: Distance measurement with ultrasonic ranger and timer
// Oluwadara Odukoya and Woolenski Placide
// 3/7/25
/*
* This program uses an ultrasonic sensor to determine the distance (cm) to the nearest object.
* First, the trigger pin is set high, this causes the ultrasonic sensor to emit an ultrasonic pulse (typically 16 pulses at 40kHz)  * signal 
* The signal goes out, is  reflected off an object, and then received by the sensor.
*`When the trigger pin sends an ultrasonic pulse, the echo pin goes high and remains high until the pulse reflects off a body and returns to the sensor
* The code measures the time between high and low states of the echo pin.
* The distance is the product of velocity of sound in air (approximatelly 34300 cm/s) and the travel time (this is distance out and back, so divide by 2).
* The TRIGGER pin on the ultrasonic sensor is connected to PL0 (output).
* The ECHO pin on the ultrasonic sensor is connected to PL1 (input).
*/

//Include the Liquid Crystal library in code
#include <LiquidCrystal.h>

//Initialize the library with the interface pin numbers used.
const int rs = 12, en = 13, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16,2); // Initialize LCD display

  DDRL = 0x01; // set PL0 as output for ultrasonic trigger and PL1 as input for ultrasonic echo
  TCCR1A = 0x00; // Set channels A, B, and C to normal port operation and normal wave generation mode.
  TCCR1B = 0b00000100; // Turn off input capture, set wave generation mode to normal, set prescale of 256.

  Serial.begin(9600);
}

void loop() {
  int time_start_bits = 0; // Will grab the start time (bit value) when the echo pin first turns HIGH
  int time_end_bits = 0; // Will grab the end time (bit value) when the echo pin turns LOW
  int duration_bits = 0; // Holds the duration (bit value) that the echo pin was on

  int trig_on_mask = 0x01, trig_off_mask = 0xFE; // Declare masks to turn ultrasonic trigger on and off
  int echo_mask = 0x02, echo_state = 0x02; // Declare masks to detect state of ultrasonic echo pin
  float duration_sec = 0.0; // Duration (seconds) that the echo pin was on
  const float ultrasonic_speed = 34300.0; // Ultrasonic speed in cm/s
  float proximity = 0.0; // Distance from ultrasonic sensor to nearest object

  // The procedure of turning off the trigger for 2 microsec, then on for 10 microsec, then back off is standard practice for this ultrasonic sensor.
  PORTL &= trig_off_mask; // Set ultrasonic trigger LOW
  delayMicroseconds(2); // Delay 2 microseconds
  PORTL |= trig_on_mask; // Set ultrasonic trigger HIGH
  delayMicroseconds(10); // Delay 10 microseconds
  PORTL &= trig_off_mask; // Set ultrasonic trigger LOW

  while((PINL & echo_mask) == 0x00){}; // Wait until the echo pin turns on
  time_start_bits = TCNT1; // Immediately after the echo pin turns on, set the start time (bit value) equal to T-COUNT 1.
  while((PINL & echo_mask) == echo_state){}; // Wait until echo pin turns back off
  time_end_bits = TCNT1; // Set the end time (bit value) equal to the new value of T-Count 1.
  duration_bits = time_end_bits - time_start_bits; // Calculate the signal duration (bit value) as the start minus the stop.
  duration_sec = float(duration_bits)*256.0/16000000.0; // Convert bit value into the signal duration in seconds.
  // Calculate distance from ultrasonic sensor to nearest object in centimeters.
  // Divide by two since the ultrasonic wave was transmitted and then reflected back.
  proximity = (ultrasonic_speed*duration_sec)/2; //proximity in cm

  Serial.print(String("Proximity: ")+String(proximity) + String("\n"));

  // Print the distance to the nearest object to the LCD screen.
  lcd.clear(); //clear LCD screen
  lcd.setCursor(0,0); //Set cursor to column 0, row 0
  lcd.print("Proximity:");
  lcd.setCursor(0,1); //Set cursor to column 0, row 1
  lcd.print(String(proximity) + String("cm")); // Print proximity value to LCD

  delay(500);
}