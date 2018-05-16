const PROGMEM  uint16_t charSet[6]  = { 1102, 2256, 3222, 4135, 5336};

struct payload_g{
  // ID: Student/Teacher
  char id;
  // State code: States of India - 2 digit number
  char s_c;
  // Area code: Area of particular state - 3 digit number (max:255) later modify to include more
  uint8_t ar_c;
  // School code: In each area - 3 digit number (max:255)later modify to include more
  uint8_t sc_c;
};

struct payload_l{
  // Class code: 1 to 10th or more - 2 digit number
  uint8_t cls_c;
  // Class section code: 2 digit number
  uint8_t cls_s_c;
  // Student code: 2 digit number
  uint8_t std_c;
};

int k; // Counter variable
unsigned int displayInt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  payload_g pay_g = {1,00,000,000};
  payload_l pay_l = {5,3,36};
  for (k=0; k<5; k++)
  {
    displayInt = pgm_read_word_near(charSet + k);   
    Serial.println("\n Student ID class"); 
    Serial.print(pay_l.cls_c);
    delay(1000);
    Serial.println("\n Class");
    Serial.print((displayInt / 1000U) % 10);
  }
  delay(1000);
}
