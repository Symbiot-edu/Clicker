
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
  Serial.begin(57600);
  Serial.print("Start");
  randomSeed(analogRead(0));
  Serial.flush();
}

void loop() {
  
  if (millis() > 100 )
  {
    if (Serial.available())
    {
      test = Serial.read();
      Serial.print(test);
      if (test=='X')
      {
        Serial.println(F("OK check R"));
        payload data = {id_ts, state_c, area_c, school_c, student_id, random(1,4)};
        Serial.print(data.id);
        sprintf(state_code, "%02d", data.s_c);
        sprintf(area_code, "%03d", data.ar_c);
        sprintf(school_code, "%03d", data.sc_c);
        sprintf(student_code, "%03d", data.std_c);
        Serial.print(state_code);
        Serial.print(area_code);
        Serial.print(school_code);
        Serial.print(student_code);
        Serial.print(data.ans_c);
        Serial.println();
      }
      /*
      if (test=='X')
      {
        Serial.println(F("OK check R"));
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
      */
    }
  }
  
}
