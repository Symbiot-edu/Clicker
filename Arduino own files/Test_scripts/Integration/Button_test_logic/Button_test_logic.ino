const int buttonPin1 = 2;     
const int buttonPin2 = 3;
const int buttonPin3 = 4;
const int buttonPin4 = 5;     

//Variables
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int flag=0;

void setup() {
  //Input or output?     
  Serial.begin(115200);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);   
  Serial.print(F("Start button test"));
  Serial.println();
}

void loop(){
  //Read button state (pressed or not pressed?)
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  Serial.println("Start");
  Serial.println(buttonState1);
  Serial.println(buttonState2);
  Serial.println(buttonState3);
  Serial.println(buttonState4);
  Serial.println("End");
  /*
  //If button pressed...
  if ((buttonState1 == HIGH) || (buttonState2 == HIGH) || (buttonState3 == HIGH) || (buttonState4 == HIGH)) { 
    //...ones, turn led on!
    flag = buttonState1*1 + buttonState2*2 + buttonState3*3 + buttonState4*4;
    Serial.print(F("The button pressed is "));
    Serial.print(flag);
    Serial.println();
  }
  delay(1000);
  */
  delay(500);
}
