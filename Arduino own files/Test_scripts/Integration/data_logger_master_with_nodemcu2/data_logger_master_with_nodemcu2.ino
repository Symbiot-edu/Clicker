/****** Registered student ID's *****/
const char std_01[] PROGMEM = "111111101";   
const char std_02[] PROGMEM = "111111102";
const char std_03[] PROGMEM = "111111103";
const char std_04[] PROGMEM = "111111104";
const char std_05[] PROGMEM = "111111105";
const char std_06[] PROGMEM = "111111106";
const char std_07[] PROGMEM = "111111107";
const char std_08[] PROGMEM = "111111108";
const char std_09[] PROGMEM = "111111109";
const char std_10[] PROGMEM = "111111110";
const char std_11[] PROGMEM = "111111111";
const char std_12[] PROGMEM = "111111112";
const char std_13[] PROGMEM = "111111113";
const char std_14[] PROGMEM = "111111114";
const char std_15[] PROGMEM = "111111115";
const char std_16[] PROGMEM = "111111116";
const char std_17[] PROGMEM = "111111117";
const char std_18[] PROGMEM = "111111118";
const char std_19[] PROGMEM = "111111119";
const char std_20[] PROGMEM = "111111120";
const char std_21[] PROGMEM = "111111121";
const char std_22[] PROGMEM = "111111122";
const char std_23[] PROGMEM = "111111123";
const char std_24[] PROGMEM = "111111124";
const char std_25[] PROGMEM = "111111125";
const char std_26[] PROGMEM = "111111126";
const char std_27[] PROGMEM = "111111127";
const char std_28[] PROGMEM = "111111128";
const char std_29[] PROGMEM = "111111129";
const char std_30[] PROGMEM = "111111130";
const char std_31[] PROGMEM = "111111131";
const char std_32[] PROGMEM = "111111132";
const char std_33[] PROGMEM = "111111133";
const char std_34[] PROGMEM = "111111134";
const char std_35[] PROGMEM = "111111135";
const char std_36[] PROGMEM = "111111136";
const char std_37[] PROGMEM = "111111137";
const char std_38[] PROGMEM = "111111138";
const char std_39[] PROGMEM = "111111139";
const char std_40[] PROGMEM = "111111140";
const char std_41[] PROGMEM = "111111141";
const char std_42[] PROGMEM = "111111142";
const char std_43[] PROGMEM = "111111143";
const char std_44[] PROGMEM = "111111144";
const char std_45[] PROGMEM = "111111145";
const char std_46[] PROGMEM = "111111146";
const char std_47[] PROGMEM = "111111147";
const char std_48[] PROGMEM = "111111148";
const char std_49[] PROGMEM = "111111149";
const char std_50[] PROGMEM = "111111150";


const char* const string_table[] PROGMEM = {std_01,std_02,std_03,std_04,std_05,std_06,std_07,
std_08,std_09,std_10,std_11,std_12,std_13,std_14,std_15,std_16,std_17,std_18,std_19,std_20,
std_21,std_22,std_23,std_24,std_25,std_26,std_27,std_28,std_29,std_30,
std_31,std_32,std_33,std_34,std_35,std_36,std_37,std_38,std_39,std_40,
std_41,std_42,std_43,std_44,std_45,std_46,std_47,std_48,std_49,std_50};

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
  Serial.begin(115200);
   
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
          for (k=0; k<50; k++)
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
