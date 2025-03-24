void setup() {
  // put your setup code here, to run once:
  DDRA = 0b11111111; // set all PORTA as outputs
  DDRC = 0b11111111;
}

long Counter = 0;

int d1_on = 0b10000000, d1_off = 0b01111111; //masks to turn digit 1 on and off
int d2_on = 0b01000000, d2_off = 0b10111111; //masks to turn digit 2 on and off
int d3_on = 0b00100000, d3_off = 0b11011111; //masks to turn digit 3 on and off
int d4_on = 0b00010000, d4_off = 0b11101111; //masks to turn digit 1 on and off

int digit[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

void loop() {
  // put your main code here, to run repeatedly:
  PORTC = 0b00000000;
  
  
  displayNumber((Counter/1000)%10);
  PORTC |= d1_on;
  delay(1);
  PORTC &= d1_off;

  
  displayNumber((Counter/100)%10);
  PORTC |= d2_on;
  delay(1);
  PORTC &= d2_off;

  
  displayNumber((Counter/10)%10);
  PORTC |= d3_on;
  delay(1);
  PORTC &= d3_off;

  
  displayNumber(Counter%10);
  PORTC |= d4_on;
  delay(1);
  PORTC &= d4_off;

  Counter++;
  delay(1000);  
}

void displayNumber(int x){
  PORTA = digit[x];
}
