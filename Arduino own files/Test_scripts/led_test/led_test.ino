int led = 2;
int state;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = HIGH;
  digitalWrite(led,state);
  delay(500);
  state = LOW;
  digitalWrite(led,state);
  delay(500);
}
