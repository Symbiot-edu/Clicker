/** Modification of RF24Mesh_Example_Master.ino by TMRh20 and RF24Mesh_Example_Master_Statics by TMRh20
 * 
 *
 * This example sketch shows how to send data to nodes bassed on their ID.
 *
 * The nodes can change physical or logical position in the network, and reconnect through different
 * routing nodes as required. The master node manages the address assignments for the individual nodes
 * in a manner similar to DHCP.
 *
 **/
 
 
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"
#include <SPI.h>
 
/***** Configure the chosen CE,CS pins *****/
RF24 radio(7,8);
RF24Network network(radio);
RF24Mesh mesh(radio,network);
 
struct payload_t {
  uint8_t check;
  char nm;
};

// Global variable which will be written and sent 
uint8_t ctr=0;
 
 
 
void setup() {
  Serial.begin(115200);
 
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  Serial.println(mesh.getNodeID());
  // Connect to the mesh
  randomSeed(analogRead(0));
  mesh.begin();
 
}
// Globale variable which will stay inside the code (not sent)
uint32_t displayTimer = 0;
 
void loop() {    
 
  // Call mesh.update to keep the network updated
  mesh.update();
 
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
 
  // Here first we read any incoming and later write an acknowledgement
  // Check for incoming data from the sensors
 
 
  // Send each node a message every five seconds
  // Send a different message to node 1, containing another counter instead of millis()
  if(millis() - displayTimer > 5000){
    ctr =  random(0, 255);
    for (int i = 0; i < mesh.addrListTop; i++) {
      // Define the payload variables
      int payload = LOW;
      Serial.print(F("The node ID is "));
      Serial.print(mesh.addrList[i].nodeID);
      // Search for the node with ID address and update corresponding ctr value
      
      RF24NetworkHeader header(mesh.addrList[i].address, OCT); //Constructing a header
      Serial.println(mesh.addrList[i].address);
      if (network.write(header, &payload, sizeof(payload))){
        Serial.println( F("Send OK"));
      }
      else{
        Serial.println( F("Send Fail")); //Sending an message
      }
    }
    displayTimer = millis();
  }
}
