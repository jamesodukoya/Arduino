#include <Servo.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo Servo1;
int servoPin = 22;

int angle = 0;
bool increasing = true;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Servo1.attach(servoPin);

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
  float delay_time = 0.0;
  float ang_vel = 0.00;

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
  delay_time = pow(duration_sec * 1000, 5);
  ang_vel = 3140/(180*delay_time);

  // Logic to control servo motor rotation
  if (increasing) { // check whether to increase rotor angle
    angle += 1; //increase by 1 degree
    if (angle == 180) {
      increasing = false;
    }
  } else {
    angle -= 1;
    if (angle == 0) {
      increasing = true;
    }
  }
  if (duration_sec < 0.00174927113){
    Servo1.write(angle);
  } // send angle input to servo motor
  lcd.clear(); // Clears the display
  lcd.print("Angular v is");
  lcd.setCursor(0, 1);
  duration_sec < 0.00174927113 ? lcd.print(String(ang_vel) + String("rad/ms")) : lcd.print("0rad/ms");
  delay(20);
}