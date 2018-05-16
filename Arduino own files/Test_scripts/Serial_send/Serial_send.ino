
unsigned long int data = 65555;
unsigned long int data2 = 555;

/*
struct payload
{
  uint32_t data1;
  uint16_t data2;
};
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("H");
  Serial.print(data);
  Serial.print("T");
  Serial.print(data2);
  delay(1000);
  
  /*
  payload data_send = {3562,122};
  Serial.write((byte*)&data_send,sizeof(data_send));
  delay(1000);
  */
  
}

