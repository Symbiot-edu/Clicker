int temp;
void setup() {
  // initialize digital pin 13 as an output.
  Serial1.flush();
  Serial1.begin(9600);
  Serial1.println("Begin Test");
}

// the loop function runs over and over again forever
void loop() {
  while(Serial1.available())
  {
    temp = Serial1.read();
    Serial.print(temp);
  }
  delay(1000);
}
