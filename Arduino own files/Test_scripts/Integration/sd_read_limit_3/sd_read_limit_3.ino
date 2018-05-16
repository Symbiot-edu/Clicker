#include <ESP8266WiFi.h>

const char* ssid = "SANDEEP_WIFI";
const char* password = "qwertyuiop";
bool bcheck=1;
bool send_data=0;
 
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
}
 
void loop() {
  while (Serial.available())
  {
    Serial.print((char)Serial.read());
  }
}
