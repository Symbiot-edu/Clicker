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
int led;
uint16_t std_id = 0001;
uint16_t displayId;
int k;
uint32_t displayTimer=0;

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
  uint8_t ans_c;
};


void setup() {
  //Input or output?     
  Serial.begin(115200); 
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
  if(millis() - displayTimer > 1000){
    Serial.print("Ok for loop works");
    Serial.println();
    for (int i = 0; i < mesh.addrListTop; i++) {
      // Define the payload variables
      // Search for the node with ID address and update corresponding ctr value
      Serial.println(mesh.addrList[i].nodeID);
      Serial.println();
      Serial.println( F("OK"));
     }
    displayTimer = millis();
  }
}
