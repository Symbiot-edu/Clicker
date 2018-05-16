uint32_t test=11;
char test_out[5] = {};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (millis() < 1000)
  {
    sprintf(test_out, "%03d", test);
    Serial.print(test_out);
    Serial.println();
    Serial.print("Checking");
    Serial.println();
    delay(100);
  }
}
