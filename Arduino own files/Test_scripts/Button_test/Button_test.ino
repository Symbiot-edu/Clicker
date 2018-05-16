const int buttonPin1 = 6;     
//const int buttonPin2 = 5;
//const int buttonPin3 = 4;
//const int buttonPin4 = 3;     

//Variables
int buttonState1 = 0;
//int buttonState2 = 0;
//int buttonState3 = 0;
//int buttonState4 = 0;
//int flag=0;

void setup() {
  //Input or output?     
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  //pinMode(buttonPin2, INPUT);
  //pinMode(buttonPin3, INPUT);
  //pinMode(buttonPin4, INPUT);   
  Serial.print(F("Start button test"));
}

void loop(){
  //Read button state (pressed or not pressed?)
  buttonState1 = digitalRead(buttonPin1);
  //buttonState2 = digitalRead(buttonPin1);
  //buttonState3 = digitalRead(buttonPin1);
  //buttonState4 = digitalRead(buttonPin1);
  
  //If button pressed...
  if (buttonState1 == HIGH) { 
    //...ones, turn led on!
    Serial.print(F("The button 1 is pressed"));
    Serial.println();
  }
  //
  //else if (buttonState2 == HIGH){
  //  Serial.print(F("The button 2 is pressed"));
  //  Serial.println();
  //}
  //else if (buttonState3 == HIGH){
  //  Serial.print(F("The button 3 is pressed"));
  //  Serial.println();
  //}
  //else if (buttonState4 == HIGH){
  //  Serial.print(F("The button 4 is pressed"));
  //  Serial.println();
  //}
  delay(200); //Small delay

}
