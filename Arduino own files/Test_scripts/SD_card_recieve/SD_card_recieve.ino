
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:

char test;
const int chipSelect = 10;
uint32_t timer=0;
Sd2Card card;
SdVolume volume;

uint8_t id_ts = 1;
uint8_t state_c = 00;
uint8_t area_c = 00;
uint8_t school_c = 00;
uint16_t student_id = 5555;
uint8_t ans = 1;
File dataFile;

struct payload{
  // ID: Student/Teacher
  uint8_t id;
  // State code: States of India - 2 digit number
  uint8_t s_c;
  // Area code: Area of particular state - 3 digit number (max:255) later modify to include more
  uint8_t ar_c;
  // School code: In each area - 3 digit number (max:255)later modify to include more
  uint8_t sc_c;
  // Student code: 2 digit number
  uint16_t std_c;
  // Answer id
  uint8_t ans_c;
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println(F("initialization failed. Things to check:"));
    Serial.println(F("* is a card inserted?"));
    Serial.println(F("* is your wiring correct?"));
    Serial.println(F("* did you change the chipSelect pin to match your shield or module?"));
    while (1);
  } else {
    Serial.println(F("Wiring is correct and a card is present."));
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
  /*

   */
   /*
   Serial.print(data.id);
   Serial.print(data.s_c);
   Serial.print(data.ar_c);
   Serial.print(data.sc_c);
   Serial.print(data.std_c);
   Serial.print(data.ans_c);
   Serial.println();
   */
  /*
  if (Serial.available())
  {
    test = (Serial.read());
    Serial.print(test);
    if (test=='R')
    {
      Serial.print("This works");
      Serial.println();
    }
  }
  */
  
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  //File dataFile = SD.open("datalog.txt", FILE_WRITE);
  /*
  if (Serial.available())
  {
    test = (Serial.read());
    Serial.print(test);
    Serial.println();
    if (test=='R')
    {
      Serial.print("OK");
      Serial.println();
    }
  }
  */
  while (millis() <= 100) {
        dataFile = SD.open("Datanew.txt",FILE_WRITE);
        if (dataFile)
        {
          //lastWriteTime = millis();
          // write data to file
          dataFile.write("blah");
          dataFile.close();  
        }
        else
        {
          Serial.println("error opening Datanew.txt");
        }
        Serial.print("Done writing");
    }
  /*
  while (millis() < 5000)
  {
    if (Serial.available())
    {
      test = Serial.read();
      if (test=='R')
      {
        Serial.println(F("OK check R"));
        payload data = {id_ts, state_c, area_c, school_c, student_id, random(1,4)};
        dataFile = SD.open("Test2.txt",FILE_WRITE);
        if (dataFile)
        {
          
          dataFile.println(data.id);
          dataFile.println(data.s_c);
          dataFile.println(data.ar_c);
          dataFile.println(data.sc_c);
          dataFile.println(data.std_c);
          dataFile.println(data.ans_c);
          dataFile.println();
          dataFile.close();
        }
        else
        {
         Serial.println("error opening test.txt"); 
        }
      }
    }
  }
  */
  
}  
