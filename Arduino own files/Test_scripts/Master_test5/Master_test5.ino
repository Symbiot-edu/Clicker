const PROGMEM  uint16_t charSet[6]  = {1102, 2256, 3222, 4135, 5336};

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

char st_c = 00;
uint8_t ar_c = 000;
uint8_t sc_c = 001;
int led = HIGH;
uint16_t std_id = 0001;
uint16_t displayId;
int k;
bool counter=false;

struct payload_g{
  // ID: Student/Teacher
  char id;
  // State code: States of India - 2 digit number
  char s_c;
  // Area code: Area of particular state - 3 digit number (max:255) later modify to include more
  uint8_t ar_c;
  // School code: In each area - 3 digit number (max:255)later modify to include more
  uint8_t sc_c;
  // Student code: 2 digit number
  uint16_t std_c;
  // Answer id
  int ans_c;
};


void setup() {
  //Input or output?     
  Serial.begin(9600);
  Serial1.begin(9600); 
  mesh.setNodeID(0);
  Serial.print(F("Begin Test"));
  Serial.println();
  Serial.println(mesh.getNodeID());
  mesh.begin();
}

void loop(){
  // Call mesh.update to keep the network updated
  mesh.update();
   
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();

  // Check network availability
  if (network.available())
  {
    RF24NetworkHeader header;
    network.peek(header);
    payload_g data;
    switch(header.type)
    {
      case 'M':
        counter = true;
        network.read(header,&data,sizeof(data));
        if ((data.s_c == st_c) && (data.ar_c == ar_c) && (data.sc_c == sc_c))
        {
          for (k=0; k<5; k++)
          {
            displayId = pgm_read_word_near(charSet + k);
            if (data.std_c == displayId)
            {
              Serial.print(F("Student Id = "));
              Serial.print(data.std_c);
              Serial.println();
              Serial.print(F("Answer = "));
              Serial.print(data.ans_c);
              Serial1.write(1);
            }
          }
        }
        else
        {
          Serial.print("State or school or area Id does not match");
        }
      default:
        network.read(header,0,0);
        Serial.println(header.type);
        break;
    }
  }
  
  if (counter==true)
  {
    for (int i=0; i<mesh.addrListTop; i++)
    {
      RF24NetworkHeader header(mesh.addrList[i].address, OCT);
      led = LOW;
      if (network.write(header, &led, sizeof(led)))
      {
        Serial.print(F("Send OK"));
        Serial.println();
      }
      else
      {
        Serial.print(F("Send Failed"));
        Serial.println();
      }
      led = HIGH;
    }
    counter = false;
  }
  
}
