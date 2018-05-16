#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <EEPROM.h>

/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(9, 10);
RF24Network network(radio);
RF24Mesh mesh(radio, network);

#define nodeID 1

const int buttonPin1 = 4;     
const int buttonPin2 = 5;
const int buttonPin3 = 6;
const int buttonPin4 = 7;     

//Variables
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
uint8_t ans=0;

uint16_t std_id = 4135;
char st_c = 00;
uint8_t ar_c = 000;
uint8_t sc_c = 001;
int led = 2;
int led_st;

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
  Serial.begin(19200);
  mesh.setNodeID(nodeID);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);   
  Serial.println(F("Connecting to the mesh..."));
  pinMode(led, OUTPUT);
  mesh.begin();
}

void loop(){
  mesh.update();
  
  //Read button state (pressed or not pressed?)
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  //If button pressed...
  if ((buttonState1 == HIGH) || (buttonState2 == HIGH) || (buttonState3 == HIGH) || (buttonState4 == HIGH)) { 
    //...ones, turn led on!
    ans = buttonState1*1 + buttonState2*2 + buttonState3*3 + buttonState4*4;
    payload_g payload_s ={1,st_c,ar_c,sc_c,std_id,ans};
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
      digitalWrite(led,HIGH);
      Serial.print("Send OK: ");
    }
    
    Serial.print(F("The button pressed is "));
    Serial.print(ans);
    Serial.println();
  }
  
  while (network.available()) {
    RF24NetworkHeader header;
    network.read(header, &led_st, sizeof(led_st));
    Serial.print("Received packet #");
    Serial.print(led_st);
    delay(500);
    digitalWrite(led,led_st);
  }
}
