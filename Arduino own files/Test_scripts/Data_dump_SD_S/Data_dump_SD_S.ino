bool R=true;
bool S=true;
char test;
char sd_read;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  if (R==true)
  {
    Serial.write('R');
    if (millis()>3000)
    {
     R=false; 
    }
  }
  
  while (Serial.available())
  {
    if (S==true)
    {
    test = Serial.read();
      if (test=='X')
      {
        sd_read = Serial.read();
        Serial.print(sd_read);
      }
    }
  }
  */
  
  while (Serial.available())
  {
    test = Serial.read();
    Serial.print(test);
  }
  
  
}
