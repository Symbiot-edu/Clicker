#include <ESP8266WiFi.h>

const char* ssid = "GANESH";
const char* password = "POOJA2017";
bool bcheck=1;
bool send_data=0;
int32_t timer=0;
 
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
 
void setup() {
  Serial.begin(57600);
 
  // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println(WiFi.localIP());
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
 
  // Set GPIO2 according to the request
  digitalWrite(2, val); 

  
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  // Send the response to the client
  if (val==1)
  { 
    Serial.print("X");
  }
  else if (val==0)
  {
    Serial.print("Y");
    while (!Serial.available())
    {
      delay(1);
    }
  }

  timer = millis();
  while ((Serial.available()) || (millis() - timer < 500))
  {
    if (Serial.available())
    {
      char t = Serial.read();
      Serial.print(t);
      s+=t;
    }
  }

  /*
  if (send_data==1)
  {
    while (Serial.available())
    {
      char t = Serial.read();
      Serial.print(t);
      s+=t;
    }
    send_data=0;
  }
  */
  
  client.print(s);
  Serial.println("Client disonnected");
 
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
