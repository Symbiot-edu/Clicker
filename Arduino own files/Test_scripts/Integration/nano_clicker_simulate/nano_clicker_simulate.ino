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
   
const int buttonPin1 = 2;     
int buttonState1 = 0;
char ans=0;
int count=1;
int random_std;
bool start=0;
bool ttime=0;

uint32_t std_id;
int led = 3;
int led_st;
int time1;
int time2;

struct payload_g{
  // Student code: 2 digit number
  uint32_t std_c;
  // Answer id
  uint8_t ans_c;
};


void setup() {
  //Input or output?     
  Serial.begin(115200);
  mesh.setNodeID(nodeID);
  Serial.println(F("Connecting to the mesh..."));
  pinMode(led, HIGH);
  pinMode(buttonPin1, INPUT);
  mesh.begin();
  randomSeed(analogRead(0));
}

void loop(){
  buttonState1 = digitalRead(buttonPin1);
  mesh.update();
    
  //If button pressed...

  if (buttonState1==HIGH)
  {
    start = !start; 
  }

  if (start==1)
  {
    time1=millis();
    while (count <= 300)
    {
      delay(20);
      random_std = random(1,50);
      std_id = 111111100 + random_std;
      
      payload_g payload_s ={std_id, random(1,5)};
      if (!mesh.write(&payload_s, 'M', sizeof(payload_s))) {
    
        // If a write fails, check connectivity to the mesh network
        if ( ! mesh.checkConnection() ) {
          //refresh the network address
          Serial.println(F("Renewing Address"));
          mesh.renewAddress();
        } else {
          //Serial.println(F("Send fail, Test OK"));
          bool sf=1;
        }
      } else {
        //Serial.print("Send OK: ");
        bool s=1;
      }
      
      count+=1;
      
    
    
      while (network.available()) {
        RF24NetworkHeader header;
        network.read(header, &led_st, sizeof(led_st));
        //Serial.print("Received packet #");
        //Serial.print(led_st);
        //Serial.println();
      }
    }
    if (count==301)
    {
      time2=millis();
      Serial.println((time2-time1)/1000);   
      start=0;
    }
    
  }
  
}
