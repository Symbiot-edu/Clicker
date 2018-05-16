/****** Registered student ID's *****/
const PROGMEM  uint32_t charSet[10]  = {100000001, 100000002, 100000003, 100000004, 
                                        100000005, 100000006, 100000007, 100000008, 100000009};

/****** Import RF42, SPI, SD and EEPROM libraries *****/
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
#include <SD.h>

/****** NRF24L01 setup *****/
RF24 radio(7, 8);           // CE and CS pins
RF24Network network(radio);
RF24Mesh mesh(radio, network);


char test;
const int chipSelect = 4;
uint32_t timer=0;
char st_code[3] = {};
char area_code[3] = {};
char school_code[4] = {};
char student_code[10] = {};
bool bcheck=1;
int k;

Sd2Card card;
SdVolume volume;

uint32_t displayId;
uint8_t state_c = 10;
uint8_t area_c = 01;
uint8_t school_c = 01;
uint32_t student_id = 00000001;
uint8_t ans = 1;
bool sd_read=false;
bool sd_send=true;
bool counter=false;
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
  SD.remove("Datasimu.txt");
  Serial.println(mesh.getNodeID());
  mesh.begin();
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
        // Call mesh.update to keep the network updated
        mesh.update();
         
        // In addition, keep the 'DHCP service' running on the master node so addresses will
        // be assigned to the sensor nodes
        mesh.DHCP();
        if (network.available())
        {
          dataFile = SD.open("SDtest2.txt",FILE_WRITE);
          RF24NetworkHeader header;
          network.peek(header);
          payload data;
          switch(header.type)
          {
            case 'M':
              counter = true;
              network.read(header,&data,sizeof(data));
              for (k=0; k<9; k++)
              {
                displayId = pgm_read_word_near(charSet + k);
                if (data.std_c == displayId)
                {
                  sprintf(st_code, "%02d", state_c);
                  dataFile.print(st_code);
                  sprintf(area_code, "%02d", area_c);
                  dataFile.print(area_code);
                  sprintf(school_code, "%03d", school_c);
                  dataFile.print(school_code);
                  sprintf(student_code, "%09d", data.std_c);
                  dataFile.print(student_code);
                  dataFile.print(data.ans_c);
                  dataFile.println();
                }
              }
            default:
              network.read(header,0,0);
              //Serial.println(header.type);
              break;
          }
        }
        dataFile.close();
      }      
      else if (test=='Y')
      {
        dataFile = SD.open("SDtest2.txt");
        if (dataFile) {
          while (dataFile.available())
          {
            Serial.print((char)dataFile.read());
          }
          dataFile.close();
        }
        else
        {
          Serial.println("error opening Data_simu.txt");
        }
        SD.remove("SDtest2.txt");
      }
      
    }
  }
  
}
