void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    Serial.print(Serial.read());
    Serial.println();
  }
}
