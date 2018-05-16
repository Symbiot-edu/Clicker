bool R=true;
bool S=true;
char test;
char sd_read[14]={};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available())
  {
    test = Serial.read();
    if (test=='X')
    {
      Serial.print("Hello");
    }
  }
  
}
