/****** Registered student ID's *****/
/*
const PROGMEM  uint32_t charSet[10]  = {12345678, 100000002, 100000003, 100000004, 
                                        100000005, 100000006, 100000007, 100000008, 100000009};
*/
const char string_0[] PROGMEM = "11111111";   // "String 0" etc are strings to store - change to suit.
const char string_1[] PROGMEM = "11111112";
const char string_2[] PROGMEM = "11111113";
const char string_3[] PROGMEM = "11111114";
const char string_4[] PROGMEM = "11111115";
const char string_5[] PROGMEM = "11111116";


// Then set up a table to refer to your strings.

const char* const string_table[] PROGMEM = {string_0,string_1,string_2,string_3,string_4,string_5};
/****** Import RF42, SPI, SD and EEPROM libraries *****/

char buffer[30];    // make sure this is large enough for the largest string it must hold
uint32_t test;
void setup()
{
  Serial.begin(9600);
  while(!Serial); // wait for serial port to connect. Needed for native USB
  Serial.println("OK");
}


void loop()
{
  /* Using the string table in program memory requires the use of special functions to retrieve the data.
     The strcpy_P function copies a string from program space to a string in RAM ("buffer").
     Make sure your receiving string in RAM  is large enough to hold whatever
     you are retrieving from program space. */


  for (int i = 0; i < 6; i++)
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy.
    Serial.println(buffer);
    String s="";
    s+= buffer;
    test = s.toInt();
    Serial.println(test);
    //Serial.println(buffer.toInt());
    delay( 500 );
  }
}
