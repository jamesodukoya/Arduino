void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);       // Initialize the Serial
   while (! Serial);       // Wait for Serial to be ready
   Serial.println("Serial is ready"); // print to the Serial port
}

void loop() {
  // put your main code here, to run repeatedly:
  // int i=0; //
  // Serial.print("none");
  // Serial.print("\t");
  // Serial.print("Dec");
  // Serial.print("t");
  // Serial.print("Bin \t")
  // Serial.print("Hex \t");

  // for ( )

    Serial.println("Hello World!"); // print to the Serial port
   delay(1000);  // delay 1000 ms
   Serial.println("goodbye World!"); // print to the serial port
   delay(1000);  // delay 1000 ms
}
