//char incomingData1 = 48;
//char incomingData2 = 48;
//char incomingData3 = 48;
//char incomingData4 = 48;
//char incomingData5 = 48;

//char Str1[6] = {incomingData1,incomingData2,incomingData3,incomingData4,incomingData5};
char Str2[6] = {};

struct payload
{
  uint32_t data1;
  uint16_t data2;
};

void setup() {
  Serial.begin(9600);
  Serial.println("Begin Test");
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //if(Serial.available()>4)
  //{
  //  incomingData1 = Serial.read();
  //  incomingData2 = Serial.read();
  //  incomingData3 = Serial.read();
  //  incomingData4 = Serial.read();
  //  incomingData5 = Serial.read();
  //  char Str1[6] = {incomingData1,incomingData2,incomingData3,incomingData4,incomingData5};
  //  Serial.println(Str1);
  //}

  
  while (Serial.available())
  {
    for (int i=0;i<5;i++)
    {
      Str2[i] = Serial.read();
    }
    Serial.println(Str2);
  }
  
  /*
  while (Serial.available())
  {
    payload data_recieve;
    if (Serial.available())
    {
      Serial.println(Serial.read());
    }
  }
  */
  delay(1000);

}

