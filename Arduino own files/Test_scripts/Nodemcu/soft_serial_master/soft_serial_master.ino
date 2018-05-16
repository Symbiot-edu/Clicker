#include <SoftwareSerial.h>

SoftwareSerial swSer(14, 12, false, 128); //Define hardware connections
 
void setup() {
  Serial.begin(115200);   //Initialize hardware serial with baudrate of 115200
  swSer.begin(115200);    //Initialize software serial with baudrate of 115200
 
  Serial.println("\nSoftware serial test started");
 
  for (char ch = ' '; ch <= 'z'; ch++) {  //send serially a to z on software serial
    swSer.write(ch);
  }
  swSer.println("");
 
}
 
void loop() {
  while (swSer.available() > 0) {  //wait for data at software serial
    Serial.write(swSer.read()); //Send data recived from software serial to hardware serial    
  }
  while (Serial.available() > 0) { //wait for data at hardware serial
    swSer.write(Serial.read());     //send data recived from hardware serial to software serial
  }
 
}
