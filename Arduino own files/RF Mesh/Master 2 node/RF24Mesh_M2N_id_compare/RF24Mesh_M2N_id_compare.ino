/** Modification of RF24Mesh_Example_Master.ino by Sandeep and RF24Mesh_Example_Master_Statics by Sandeep
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
RF24 radio(9,10);
RF24Network network(radio);
RF24Mesh mesh(radio,network);
 
// Global variable which will be written and sent 
uint8_t cls_id=53;

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
 
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  Serial.println(mesh.getNodeID());
  // Connect to the mesh
  randomSeed(analogRead(0));
  mesh.begin();
}

// Globale variable which will stay inside the code (not sent)
uint32_t displayTimer = 0;
bool led=false;

void loop() {    
 
  // Call mesh.update to keep the network updated
  mesh.update();
 
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
 
  // Here first we read any incoming and later write an acknowledgement
  // Check for incoming data from the sensors
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);
    Serial.print("Got ");
    // Internal local variable to assign the incoming data
    payload_g id; 
    switch(header.type){
      // Display the incoming millis() values from the sensor nodes
    case 'M': 
      network.read(header,&id,sizeof(id));
      if (id.cls_c == (cls_id/10U)%10)
      {
        if (id.sec_c == cls_id%10)
        {
          Serial.print(id.cls_c);
          Serial.print(id.sec_c);
          Serial.println();
          Serial.println("Answer");
          Serial.print(id.ans_c);
          break;
        }
      }
    default: 
      network.read(header,0,0); 
      Serial.println(header.type);
      break;
    }
  }
 
 
  // Send each node a message every five seconds
  // Send a different message to node 1, containing another counter instead of millis()
  if(millis() - displayTimer > 5000){
    for (int i = 0; i < mesh.addrListTop; i++) {
      // Define the payload variables
      // Search for the node with ID address and update corresponding ctr value
      if (mesh.addrList[i].nodeID == 1) {  //Searching for node one from address list
        led = true;
      }
      RF24NetworkHeader header(mesh.addrList[i].address, OCT); //Constructing a header
      if (network.write(header, &led, sizeof(led))){
        Serial.println( F("Send OK"));
      }
      else{
        Serial.println( F("Send Fail")); //Sending an message
      }
      led = false;
    }
    displayTimer = millis();
  }
}
