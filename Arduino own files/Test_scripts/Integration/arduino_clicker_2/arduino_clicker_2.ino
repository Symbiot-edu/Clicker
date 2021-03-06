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
char ans=0;

uint32_t std_id = 11111111;
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
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);   
  Serial.println(F("Connecting to the mesh..."));
  pinMode(led, HIGH);
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
    payload_g payload_s ={std_id,ans};
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
    Serial.print(payload_s.ans_c);
    Serial.println();
  }
  
  while (network.available()) {
    RF24NetworkHeader header;
    network.read(header, &led_st, sizeof(led_st));
    Serial.print("Received packet #");
    Serial.print(led_st);
    Serial.println();
  }
  if (led_st==LOW)
  {
    delay(200);
    digitalWrite(led,led_st);
  }
  delay(100);
}
