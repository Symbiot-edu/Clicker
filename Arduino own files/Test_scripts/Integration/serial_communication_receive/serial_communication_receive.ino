#include <ESP8266WiFi.h>

const char* ssid = "SANDEEP_WIFI";
const char* password = "qwertyuiop";
int32_t timer =0;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  Serial.println();
  Serial.print("Connecting to");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  server.begin();
  Serial.print("Server started");

  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
 
  while (!Serial.available())
  {
    Serial.print("Break");
    delay(1);
  }
  

  while (Serial.available() || (millis()-timer > 5000))
  {
    if (Serial.available())
    {
      char t = Serial.read();
      Serial.print(t); 
    } 
  }
  timer = millis();
  delay(500);
}
