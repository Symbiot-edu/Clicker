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
  
  if (R==true)
  {
    Serial.print('R');
    delay(1000);
    if (millis()>3000)
    {
     R=false;
     Serial.write('S'); 
    }
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
      /*
      if (test=='S')
      {
        for(int i=0;i<13;i++)
        {
          sd_read[i] = Serial.read();
          Serial.println(sd_read); 
        }
        //S=false; 
      }
      */
    }
  }
  

  
  
  /*
  while (Serial.available())
  {
    test = Serial.read();
    Serial.print(test);
  }
  */
  
}
