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
  int ans_c;
};

payload_g data = {0,000,000,000,1212,5};

void setup()
{
  Serial.begin(9600);
}

void loop()
{  
  //byte buf[4];
  //buf[0] = data & 255;
  //buf[1] = (data >> 8)  & 255;
  //buf[2] = (data >> 16) & 255;
  //buf[3] = (data >> 24) & 255;
  
  //unsigned char *p = (unsigned char*)&data;
  
  //Serial.print(sizeof(data));
  //Serial.print(p[0]);
  //unsigned char *p;
  //for (int i=0; i<sizeof(data);i++)
  //{
  //  p[i] = data;
  //}
  //Serial.print(p[0]);
  Serial.write((byte*)&data, sizeof(data));
  delay(1000);
}
