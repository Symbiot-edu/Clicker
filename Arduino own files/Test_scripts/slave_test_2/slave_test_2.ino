#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 1

uint32_t displayTimer=0;
int data;

void setup() {
  //Input or output?     
  Serial.begin(115200);
  mesh.setNodeID(nodeID);
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin();
}

void loop(){
  mesh.update();
  
  //Read button state (pressed or not pressed?)
  
  //If button pressed...
  if (millis() - displayTimer >= 200) {
    displayTimer = millis();
    data = 4;
    
    // Send an 'M' type message containing the current millis()
    if (!mesh.write(&data, 'M', sizeof(data))) {

      // If a write fails, check connectivity to the mesh network
      if ( ! mesh.checkConnection() ) {
        //refresh the network address
        Serial.println("Renewing Address");
        mesh.renewAddress();
      } else {
        Serial.println("Send fail, Test OK");
      }
    } else {
      Serial.print("Send OK: ");
      Serial.println(displayTimer);
    }
  }

}
