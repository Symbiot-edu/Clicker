#include <SPI.h>
#include <SD.h>

File myFile;

uint32_t timer;
char test;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.print("Begin Test");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis() <= 3000)
  {
    Serial.print("R");  
  }


  /*
  if (millis() > 5000)
  {
    if (Serial.available())
    {
     test = Serial.read();
     Serial.println(test);
     if (test=='X')
     {
      myFile = SD.open("Datanew.txt");
      if (myFile)
      {
        Serial.println("Datanew.txt:");
        while(myFile.available())
        {
         Serial.write(myFile.read());
          
        }
        myFile.close();
      }
      else
      {
       Serial.println("error opening Datanew.txt"); 
      }
     }
    }
  }
  */

  myFile = SD.open("Datanew.txt");
  if (myFile)
  {
    Serial.println("Datanew.txt:");
    while(myFile.available())
    {
      Serial.write(myFile.read());
      
    }
    myFile.close();
  }
  else
  {
    Serial.println("error opening Datanew.txt"); 
  }
  
  delay(1000);
}
