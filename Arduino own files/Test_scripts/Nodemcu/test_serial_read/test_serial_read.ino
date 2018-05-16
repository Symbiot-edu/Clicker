char test;
char test2;
bool count=1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (Serial.available() > 0)
  {
    char t=Serial.read();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (count==1)
  {
    while (Serial.available())
    {
      test = Serial.read();
      Serial.println(test);
      if (test == 'S')
      {
        Serial.print("Test Complete");
      }  
    }
  }
  delay(1000);
}


