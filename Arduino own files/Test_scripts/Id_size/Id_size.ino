uint32_t a = 19999999944;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(sizeof(a));
  Serial.println();
  Serial.print(a);
  Serial.println();
  delay(1000);
}
