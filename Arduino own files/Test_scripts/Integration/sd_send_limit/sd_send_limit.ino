#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:
const int chipSelect = 4;
Sd2Card card;
SdVolume volume;
File dataFile;

char st_code[3] = {};
char area_code[3] = {};
char school_code[4] = {};
char student_code[9] = {};
bool start=1;


uint8_t state_c = 10;
uint8_t area_c = 01;
uint8_t school_c = 01;
uint32_t student_id = 00000001;
uint8_t ans = 1;


struct payload{
  // Student code: 2 digit number
  uint32_t std_c;
  // Answer id
  uint8_t ans_c;
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println(F("initialization failed. Things to check:"));
    Serial.println(F("* is a card inserted?"));
    Serial.println(F("* is your wiring correct?"));
    Serial.println(F("* did you change the chipSelect pin to match your shield or module?"));
    while (1);
  } else {
    //Serial.println(F("Wiring is correct and a card is present."));
  }
  
  if (!SD.begin(chipSelect)) {
    Serial.println(1);
    while (1);
  }
  randomSeed(analogRead(0));
  Serial.flush();
}

void loop() {
  dataFile = SD.open("Sdata.txt",FILE_WRITE);
  if (start==1)
  {
    if (dataFile)
    {
      for (int i=0;i<30;i++)
      {
        payload data = {random(00000001,00000005), random(1,4)};
        sprintf(st_code, "%02d", state_c);
        Serial.print(st_code);
        dataFile.print(st_code);
        sprintf(area_code, "%02d", area_c);
        Serial.print(area_code);
        dataFile.print(area_code);
        sprintf(school_code, "%03d", school_c);
        Serial.print(school_code);
        dataFile.print(school_code);
        sprintf(student_code, "%09d", data.std_c);
        Serial.print(student_code);
        dataFile.print(student_code);
        Serial.print(data.ans_c);
        dataFile.print(data.ans_c);
        Serial.print('\n');
        dataFile.println();
      }
    }
    else
    {
      Serial.println(F("error opening Sdata.txt")); 
    }
   dataFile.close();
   SD.remove("Sdata.txt");
   start=0;
  } 
}
