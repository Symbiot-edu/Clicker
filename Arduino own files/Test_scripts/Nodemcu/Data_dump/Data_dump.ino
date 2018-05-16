#include <dummy.h>

bool R=true;
bool S=true;
char test;
//char sd_read[14]={};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if ((R==true))
  {
    Serial.print('R');
    delay(1000);
  }

  
  while (Serial.available())
  {
    if (S==true)
    {
      test = Serial.read();
      if(test=='E')
      {
        S=false;
      }
      else
      {
        Serial.print(test);
      }
    }
  }
  

}
