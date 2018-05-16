
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:

char test;
const int chipSelect = 10;
uint32_t timer=0;
char st_code[3] = {};
char area_code[3] = {};
char school_code[4] = {};
char student_code[9] = {};
bool bcheck=1;

Sd2Card card;
SdVolume volume;

uint8_t state_c = 10;
uint8_t area_c = 01;
uint8_t school_c = 01;
uint32_t student_id = 00000001;
uint8_t ans = 1;
bool sd_read=false;
bool sd_send=true;
File dataFile;

struct payload{
  // Student code: 2 digit number
  uint32_t std_c;
  // Answer id
  uint8_t ans_c;
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  randomSeed(analogRead(0));
  Serial.flush();
}

void loop() {
  if (bcheck==1)
  {
    if (Serial.available()>0)
    {
      char buf_empty = Serial.read();
    }
    bcheck=0;
  }

  
  if (bcheck==0)
  {
    while (Serial.available())
    {
      test = Serial.read();
      if (test=='X')
      {
        for (int i=0;i<4;i++)
        {
          payload data = {random(00000001,00000005), random(1,4)};
          sprintf(st_code, "%02d", state_c);
          Serial.print(st_code);
          sprintf(area_code, "%02d", area_c);
          Serial.print(area_code);
          sprintf(school_code, "%03d", school_c);
          Serial.print(school_code);
          sprintf(student_code, "%09d", data.std_c);
          Serial.print(student_code);
          Serial.print(data.ans_c);
          Serial.println(); 
        }
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
