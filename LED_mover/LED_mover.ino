long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 300;    // the debounce time; increase if the output flickers

int mask = 0b11110000; // declare mask to check state of SW0, SW1, SW2, and SW3

int position = 0, direction = 0; // declare variables to store present position of LED and direction to move

int left = 254, right = 253, up = 251, down = 247; // declare variables to store button click values

int positions[8] = {0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000}; // light up each LED from A,B,C,... to DP

void setup() {
  // put your setup code here, to run once:
  DDRA = 0b11111111; // set all PORTA (print number) as outputs
  DDRC = 0b11111111; // set all PORTC (digit selector) as outputs
  PORTC = 0b01110000; // turn on only digit 1

  DDRL = 0x00; // PORTL all inputs (switches)
  PORTL = 0b00001111; // set pull up resistors on PL0, PL1, PL2, and PL3

  Serial.begin(9600); // init serial print
  Serial.println("Serial communication is ready");
}

void loop() {
  // put your main code here, to run repeatedly:

  PORTA = 0b01000000; // turn on the center LED

  while(1){ // Use an infinite loop to avoid reseting the LED status to the center
    while ((PINL | mask) == 0xFF){}; // Check for pushbutton press
    if ( (millis() - lastDebounceTime) > debounceDelay) { // Fix debounce logic
      position = PORTA, direction = PINL; // Capture present position of LED and required direction to move based on button press
      moveLED(position, direction); // Implement LED status change
      // Serial.print(String(position) + String("\n") + String(direction) + String("\n"));
      lastDebounceTime = millis(); // assign present time to lastDebounceTime
    }
  }
}

// Change LED position
void moveLED(int pos, int dir){
  switch(pos){
    case 1: // When initial energized LED is A
      if (dir == left){
        PORTA = positions[5];
      } else if (dir == right){
        PORTA = positions[1];
      } else if (dir == up){
        PORTA = positions[0];
      } else {
        PORTA = positions[6];
      }
    break;
    case 2: // When initial energized LED is B
      if (dir == left){
        PORTA = positions[5];
      } else if (dir == right){
        PORTA = positions[7];
      } else if (dir == up){
        PORTA = positions[0];
      } else {
        PORTA = positions[6];
      }
    break;
    case 4: // When initial energized LED is C
      if (dir == left){
        PORTA = positions[4];
      } else if (dir == right){
        PORTA = positions[7];
      } else if (dir == up){
        PORTA = positions[6];
      } else {
        PORTA = positions[3];
      }
    break;
    case 8: // When initial energized LED is D
      if (dir == left){
        PORTA = positions[4];
      } else if (dir == right){
        PORTA = positions[2];
      } else if (dir == up){
        PORTA = positions[6];
      } else {
        PORTA = positions[7];
      }
    break;
    case 16: // When initial energized LED is E
      if (dir == left){
        PORTA = positions[4];
      } else if (dir == right){
        PORTA = positions[2];
      } else if (dir == up){
        PORTA = positions[6];
      } else {
        PORTA = positions[3];
      }
    break;
    case 32: // When initial energized LED is F
      if (dir == left){
        PORTA = positions[5];
      } else if (dir == right){
        PORTA = positions[1];
      } else if (dir == up){
        PORTA = positions[0];
      } else {
        PORTA = positions[6];
      }
    break;
    case 64: // When initial energized LED is G
      if (dir == left){
        PORTA = positions[5];
      } else if (dir == right){
        PORTA = positions[1];
      } else if (dir == up){
        PORTA = positions[0];
      } else {
        PORTA = positions[3];
      }
    break;
    case 128: // When initial energized LED is DP
      if (dir == left){
        PORTA = positions[3];
      } else if (dir == right){
        PORTA = positions[7];
      } else if (dir == up){
        PORTA = positions[2];
      } else {
        PORTA = positions[7];
      }
    break;
  }
}