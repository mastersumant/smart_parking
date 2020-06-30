#include <Keypad.h>
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>
#define FIREBASE_HOST "smart-parking-2-acf48.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "u8UXUiWZUNXBScesW97PNpolPeLGN03h4LC4VCEi"                    // the secret key generated from firebase
#define WIFI_SSID "mastersumant"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "sumantkvs" 
#define Password_Lenght 4
int fireStatus;   
const byte ROWS = 4;
const byte COLS = 3;
char Data[Password_Lenght];
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
int a;

byte data_count = 0;
byte rowPins[ROWS] = {D0,D1,D2,D3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D4,D5,D6}; //connect to the column pinouts of the keypad


Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
     Serial.begin(9600);
}
char customKey;

void loop()
{
   customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    data_count++;
  }
   if (data_count == Password_Lenght - 1)
   {
      a=atoi(Data);
     Serial.println(a);   
}
 if (a==fireStatus) {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, HIGH);                                                  // make bultin led ON
                                                           // make external led ON
  } 
}
