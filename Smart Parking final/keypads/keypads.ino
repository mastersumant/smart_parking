#include <Keypad.h>
const byte ROWS = 2;
const byte COLS = 2;
char keys[ROWS][COLS] = {
  {'1', '2'},
  {'4', '5'}
 
};



byte rowPins[ROWS] = {16,5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4,0}; //connect to the column pinouts of the keypad


Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
     Serial.begin(9600);
}
char customKey;

void loop()
{
   customKey = customKeypad.getKey();
   Serial.println(customKey);
}
