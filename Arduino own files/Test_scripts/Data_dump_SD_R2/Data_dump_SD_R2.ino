
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:

char test;
const int chipSelect = 10;
uint32_t timer=0;
char state_code[3] = {};
char area_code[3] = {};
char school_code[4] = {};
char student_code[5] = {};

Sd2Card card;
SdVolume volume;

uint8_t id_ts = 1;
uint8_t state_c = 01;
uint8_t area_c = 01;
uint8_t school_c = 01;
uint16_t student_id = 5555;
uint8_t ans = 1;
bool sd_read=false;
bool sd_send=true;
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
  
  //Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  /*
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println(F("initialization failed. Things to check:"));
    Serial.println(F("* is a card inserted?"));
    Serial.println(F("* is your wiring correct?"));
    Serial.println(F("* did you change the chipSelect pin to match your shield or module?"));
    while (1);
  } else {
    Serial.println(F("Wiring is correct and a card is present."));
  }
  */
  if (!SD.begin(chipSelect)) {
    Serial.println(1);
    while (1);
  }
  randomSeed(analogRead(0));
  Serial.flush();
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


  /*
  Serial.print(millis());
  Serial.println("Start");
  while (millis() <= 10000) {
      dataFile = SD.open("Data2.txt",FILE_WRITE);
      if (dataFile)
      {
        //lastWriteTime = millis();
        // write data to file
        dataFile.write("blah");
        dataFile.close();  
      }
      else
      {
        Serial.println("error opening Data2.txt");
      }
  }
  Serial.println("Stop");
  delay(1000);
  */
  
  
  
  
  if (millis() > 100)
  {
    if (Serial.available())
    {
      test = Serial.read();
      if (test=='R')
      {
        //Serial.println(F("OK check R"));
        payload data = {id_ts, state_c, area_c, school_c, student_id, random(1,4)};
        dataFile = SD.open("Datanew.txt",FILE_WRITE);
        if (dataFile)
        {
          dataFile.print(data.id);
          sprintf(state_code, "%02d", data.s_c);
          sprintf(area_code, "%03d", data.ar_c);
          sprintf(school_code, "%03d", data.sc_c);
          sprintf(student_code, "%03d", data.std_c);
          dataFile.print(state_code);
          dataFile.print(area_code);
          dataFile.print(school_code);
          dataFile.print(student_code);
          dataFile.print(data.ans_c);
          dataFile.println();
          dataFile.close();
        }
        else
        {
         Serial.println(F("error opening outputnew.txt")); 
        }
      }
      else if (test=='S')
      {
        //Serial.println(test);
        dataFile = SD.open("Datanew.txt");
        if (dataFile) {
        while (dataFile.available())
        {
          Serial.write(dataFile.read());
        }
        dataFile.close();
        }
        // if the file isn't open, pop up an error:
        else
        {
          Serial.println("error opening Datanew.txt");
        }
        Serial.write('E');
      }
    }
  }
  
  
  delay(1000);
}
