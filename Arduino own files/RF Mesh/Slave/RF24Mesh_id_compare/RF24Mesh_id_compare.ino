
/** RF24Mesh_Example.ino by TMRh20
 *
 * This example sketch shows how to manually configure a node via RF24Mesh, and send data to the
 * master node.
 * The nodes will refresh their network address as soon as a single write fails. This allows the
 * nodes to change position in relation to each other and the master node.
 */


#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>
//#include <printf.h>


/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

/**
 * User Configuration: nodeID - A unique identifier for each radio. Allows addressing
 * to change dynamically with physical changes to the mesh.
 *
 * In this example, configuration takes place below, prior to uploading the sketch to the device
 * A unique value from 1-255 must be configured for each node.
 * This will be stored in EEPROM on AVR devices, so remains persistent between further uploads, loss of power, etc.
 *
 **/
#define nodeID 1


uint32_t displayTimer = 0;
char ans;
bool led=false;

struct payload_g{
  // ID: Student/Teacher
  char id;
  // State code: States of India - 2 digit number
  char s_c;
  // Area code: Area of particular state - 3 digit number (max:255) later modify to include more
  uint8_t ar_c;
  // School code: In each area - 3 digit number (max:255)later modify to include more
  uint8_t sc_c;
  // Class code: 1 to 10th or more - 2 digit number
  uint8_t cls_c;
  // Class section code: 2 digit number
  uint8_t sec_c;
  // Student code: 2 digit number
  uint8_t std_c;
  // Answer id
  char ans_c;
};

void setup() {

  Serial.begin(115200);
  //printf_begin();
  // Set the nodeID manually
  mesh.setNodeID(nodeID);
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh..."));
  randomSeed(analogRead(0));
  mesh.begin();
}


void loop() {

  mesh.update();

  // Send to the master node every second
  // Internal delay to send data
  if (millis() - displayTimer >= 1000) {
    displayTimer = millis();
    ans = random(1,4);
    payload_g payload_s ={1,000,000,000,5,3,12,ans};
    
    // Send an 'M' type message containing the current millis()
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
      Serial.print("Send OK: "); Serial.println(displayTimer);
    }
  }

  while (network.available()) {
    RF24NetworkHeader header;
    network.read(header, &led, sizeof(led));
    Serial.print("Received packet #");
    Serial.print(led);
    led = false;
  }
}






