/****** Registered student ID's *****/
const char std_01[] PROGMEM = "111111111";   
const char std_02[] PROGMEM = "111111112";
const char std_03[] PROGMEM = "111111113";
const char std_04[] PROGMEM = "111111114";
const char std_05[] PROGMEM = "111111115";
const char std_06[] PROGMEM = "111111116";


const char* const string_table[] PROGMEM = {std_01,std_02,std_03,std_04,std_05,std_06};
char buffer[10];    // make sure this is large enough for the largest string it must hold

/****** Import RF42, SPI, SD and EEPROM libraries *****/
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <EEPROM.h>



/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(6,7);
RF24Network network(radio);
RF24Mesh mesh(radio, network);
char st_code[3] = {};
char area_code[3] = {};
char school_code[4] = {};
char student_code[10] = {};
bool std_check=0;
int led = HIGH;
uint32_t displayId;
int count=0;

int k;
bool counter=false;
bool sd_read=1;
bool bcheck=1;
char test;
bool data_log_r=0;

uint8_t state_c = 10;
uint8_t area_c = 01;
uint8_t school_c = 01;
struct payload_g{
  // Student code: 2 digit number
  uint32_t std_c;
  // Answer id
  uint8_t ans_c;
};


#include <SPI.h>
#include "SdFat.h"
#if ENABLE_SOFTWARE_SPI_CLASS  // Must be set in SdFat/SdFatConfig.h
//
// Pin numbers in templates must be constants.
const uint8_t SOFT_MISO_PIN = 10;
const uint8_t SOFT_MOSI_PIN = 9;
const uint8_t SOFT_SCK_PIN  = 8;
//
// Chip select may be constant or RAM variable.
const uint8_t SD_CHIP_SELECT_PIN = 4;

// SdFat software SPI template
SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> SD;

// Test file.
File dataFile;


void setup() {
  //Input or output?     
  Serial.begin(57600);
  while (!Serial) {
    SysCall::yield(); // wait for serial port to connect. Needed for native USB port only
  }
   
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  
  
  if (!SD.begin(SD_CHIP_SELECT_PIN)) {
    Serial.println("initialization failed!");
    return;
  }

  if (SD.exists("SDtest3.txt"))
  {
    SD.remove("SDtest3.txt");
  }
  
  mesh.setNodeID(0);
  Serial.print(F("Begin Test"));
  Serial.println();
  Serial.println(mesh.getNodeID());
  mesh.begin();
}

void loop(){
  if (bcheck==1)
  {
    while (Serial.available())
    {
      char buf_empty = Serial.read();
    }
    bcheck=0;
  }
  // Call mesh.update to keep the network updated
  mesh.update();
   
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();

  // Reading the serial data from nodemcu
  if (bcheck==0)
  {
    while (Serial.available())
    {
      test = Serial.read(); 
    }
  }

  // Flag based data collection
  if ((test=='X') || (data_log_r==1))
  {
    // Flag to continue extracting data
    data_log_r = 1;
    if (network.available())
    {
      // Network header 
      RF24NetworkHeader header;
      network.peek(header);
      dataFile = SD.open("SDtest3.txt", FILE_WRITE);
      payload_g data;

      // Swtich cases
      switch(header.type)
      {
        case 'M':
          counter = true;
          network.read(header,&data,sizeof(data));

          // Compare with lookup table
          for (k=0; k<6; k++)
          {
            strcpy_P(buffer, (char*)pgm_read_word(&(string_table[k]))); // Necessary casts and dereferencing, just copy.
            String s="";
            s+= buffer;
            displayId = s.toInt();
            if (data.std_c == displayId)
            {
              sprintf(st_code, "%02d", state_c);
              dataFile.print(st_code);
              sprintf(area_code, "%02d", area_c);
              dataFile.print(area_code);
              sprintf(school_code, "%03d", school_c);
              dataFile.print(school_code);
              sprintf(student_code, "%09d", data.std_c);
              dataFile.print(displayId);
              dataFile.print(data.ans_c);
              dataFile.println();
              std_check = 1;
            }
          }
  
          if (std_check==1)
          {
            std_check = 0;
          }
          else
          {
            Serial.println(F("Student ID does not match"));
          }
        default:
          network.read(header,0,0);
          //Serial.println(header.type);
          break;
      }
      dataFile.close();
    }

    // Acknowledgement packet
    
    if (counter==true)
    {
      for (int i=0; i<mesh.addrListTop; i++)
      {
        RF24NetworkHeader header(mesh.addrList[i].address, OCT);
        led = LOW;
        if (network.write(header, &led, sizeof(led)))
        {
          bool net_check=1;
        }
        else
        {
          bool net_check=0;
        }
        led = HIGH;
      }
      counter = false;
    }
  }
  
  if (test=='Y')
  {
    data_log_r=0;
    dataFile = SD.open("SDtest3.txt");
    if (dataFile) 
    {
      while (dataFile.available())
      {
        Serial.print((char)dataFile.read());
      }
      dataFile.close();
    }
    else
    {
     Serial.println("error opening SDtest3.txt");
    }
    //SD.remove("SDtest3.txt"); 
  }

}
#else  // ENABLE_SOFTWARE_SPI_CLASS
#error ENABLE_SOFTWARE_SPI_CLASS must be set non-zero in SdFat/SdFatConfig.h
#endif  //ENABLE_SOFTWARE_SPI_CLASS
