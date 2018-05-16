#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(6,7);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 1
   

char ans=0;
int count=1;

uint32_t std_id = 111111111;
int led = 3;
int led_st;

struct payload_g{
  // Student code: 2 digit number
  uint32_t std_c;
  // Answer id
  uint8_t ans_c;
};


void setup() {
  //Input or output?     
  Serial.begin(57600);
  mesh.setNodeID(nodeID);
  Serial.println(F("Connecting to the mesh..."));
  pinMode(led, HIGH);
  mesh.begin();
}

void loop(){
  mesh.update();
    
  //If button pressed...
  while (count <= 50)
  {
    delay(20);
    payload_g payload_s ={random(111111111,111111117), random(1,5)};
    if (!mesh.write(&payload_s, 'M', sizeof(payload_s))) {
  
      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println(F("Renewing Address"));
        mesh.renewAddress();
      } else {
        Serial.println(F("Send fail, Test OK"));
      }
    } else {
      Serial.print("Send OK: ");
    }
    
    Serial.print(payload_s.std_c);
    Serial.print(payload_s.ans_c);
    Serial.println();
    count+=1;
    Serial.println(count);
  }
  
  while (network.available()) {
    RF24NetworkHeader header;
    network.read(header, &led_st, sizeof(led_st));
    Serial.print("Received packet #");
    Serial.print(led_st);
    Serial.println();
  }
}
