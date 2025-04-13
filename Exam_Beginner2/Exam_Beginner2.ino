long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 300;    // the debounce time; increase if the output flickers

int mask = 0b11110000; // declare mask to check state of SW0, SW1, SW2, and SW3

int command = 0;

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

long delayTime = 83;

void loop() {
  // put your main code here, to run repeatedly:

  delayTime = 83;

  while((PINL | mask) != 0b11111110){}; // Wait until SW1 is pressed

  if ( (millis() - lastDebounceTime) > debounceDelay) { // Fix debounce logic
    count(); // call Counter function
    lastDebounceTime = millis(); // assign present time to lastDebounceTime
  }
}

void count(){
  for (int i=0; i<6; i++){
    if ((PINL | mask) != 0b11111111){ // Check if SW has been pressed
      if ( (millis() - lastDebounceTime) > debounceDelay) { // debounce logic
        command = PINL | mask;
        Serial.print(String(delayTime)+"\n");
        processSwitch(command);
        lastDebounceTime = millis();
      }
    }
    PORTA = positions[i];
    delay(delayTime);
  }
  count();
}

void processSwitch(int com){
  switch(com){
    case 254:
      {}
    break;
    case 253:
      delayTime = delayTime/2;
    break;
    case 251:
      delayTime = delayTime*2;
    break;
    case 247:
      PORTA = 0x00;
      loop();
    break;
  }
}