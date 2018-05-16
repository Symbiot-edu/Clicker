//const PROGMEM  uint16_t charSet[6]  = { 1102, 2256, 3222, 4135, 5336};

struct payload_g{
  // ID: Student/Teacher
  char id;
  // State code: States of India - 2 digit number
  char s_c;
  // Area code: Area of particular state - 3 digit number (max:255) later modify to include more
  uint8_t ar_c;
  // School code: In each area - 3 digit number (max:255)later modify to include more
  uint8_t sc_c;
  // Class code: 1 to 10th or more - 2 digit number
  uint8_t cls_c;
  // Class section code: 2 digit number
  uint8_t sec_c;
  // Student code: 2 digit number
  uint8_t std_c;
};


int k; // Counter variable
uint8_t rd;
uint8_t rd2;
uint8_t class_num = 22;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  rd = random(1,10);
  rd2 = random(1,10);
  payload_g pay_l = {1,00,000,000,rd,rd2,36};
  for (k=0; k<5; k++)
  {
    if (pay_l.cls_c == (class_num/10U)%10)
    {
     if (pay_l.sec_c == (class_num%10))
     {
      Serial.println("\n Student ID class"); 
      Serial.print(pay_l.cls_c);
      Serial.println("\n Student section"); 
      Serial.print(pay_l.sec_c);
     }
    }
  }
  delay(1000);
}
