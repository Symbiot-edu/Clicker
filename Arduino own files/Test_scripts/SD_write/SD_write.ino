#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;
bool check=1;
bool check_read=1;

File dataFile;
unsigned long lastWriteTime = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}


void loop() {

    /*
    if (check==1)
    {
      dataFile = SD.open("Datatestnew.txt",FILE_WRITE);
      for (int i=0;i<4;i++)
      {
        if (dataFile)
        {
          lastWriteTime = millis();
          // write data to file
          dataFile.write("blah");
          dataFile.close();  
        }
        else
        {
          Serial.println("error opening Datatestnew.txt");
        } 
      }
      check=0;
    }
    */

    if (check==1)
    {
      dataFile = SD.open("SDtest.txt",FILE_WRITE);
      if (dataFile)
      {
        for (int i=0;i<4;i++)
        {
          dataFile.print("blah");
          dataFile.println();
        }
        dataFile.close();   
      }
      else
      {
        Serial.println("error opening SDtest.txt");
      }
      check=0;
    }
    
    if (check_read==1)
    {
      dataFile = SD.open("SDtest.txt");
      if (dataFile) {
        while (dataFile.available())
        {
          char t = dataFile.read();
          Serial.print(t);
        }
        dataFile.close();
      }
      else
      {
        Serial.println("error opening SDtest.txt");
      }
      //Serial.println("Removing example.txt...");
      //SD.remove("SDtest.txt");
      check_read=0; 
    }
    delay(500);
      
}
