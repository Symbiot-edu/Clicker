// Student ID written as lookup table
const PROGMEM  uint16_t charSet[6]  = {1102, 2256, 3222, 4135, 5336};

// For serial communication
#include <SPI.h>
// For writing the lookup table inside its SRAM
#include <EEPROM.h>

// Timer variable
uint32_t Timer = 0;
// Id 
uint16_t ID;
// Answer variable
uint8_t ans=0;
// Flag for sending data
char test;

void setup() {
  // Begin communication 
  Serial.begin(9600);
  // Seed for true random process
  randomSeed(analogRead(0));
}

void loop() {
  // Check if any serial data available 
  while (Serial.available())
  {
    test = Serial.read();
    if (test=='X')
    {
      while (millis() - Timer < 10000)
      {
        ID = pgm_read_word_near(charSet + random(0,4));
        ans = random(1,4);
        Serial.print(ID);
        Serial.print(ans);
        Serial.println();
        delay(500);
      }
      Timer = millis();
    }
  }
}
