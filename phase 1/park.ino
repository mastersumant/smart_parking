#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library
#include <Keypad.h>
#define FIREBASE_HOST "smart-parking-2-acf48.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "u8UXUiWZUNXBScesW97PNpolPeLGN03h4LC4VCEi"                    // the secret key generated from firebase
#define WIFI_SSID "mastersumant"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "sumantkvs"                                    //password of wifi ssid
#define Password_Lenght 4
int fireStatus;                                                     // led status received from firebase
int led = D3;
char Data[Password_Lenght];
int toString(char []);
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {D0,D1,D2,D3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D4,D5,D6}; //connect to the column pinouts of the keypad
char customKey;
byte data_count = 0;
Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad
                                                                                                    // for external led
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);      
  pinMode(led, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  Firebase.setInt("LED_STATUS",123);                                          //send initial string of led status
}


int a;

void loop() {
  void Open();
  customKey = customKeypad.getKey();
  Serial.println(customKey);
 
}
void Open()
{
  customKey = customKeypad.getKey();
  if (customKey!=NO_KEY) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    data_count++;
  }                     // increment data array by 1 to store new char, also keep track of the number of chars entered
  
Serial.println(customKey);
  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
     a=atoi(Data);
     Serial.println(a);
     fireStatus = Firebase.getInt("LED_STATUS");
  Serial.println( Firebase.getInt("LED_STATUS"));  
     if (a==fireStatus) {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                                  // make bultin led ON
    digitalWrite(led, HIGH);                                                         // make external led ON
  } 
 clearData();
  }
}
void clearData()
{
  while (data_count != 0)
  { // This can be used for any array size,
    Data[data_count--] = 0; //clear array for new data
  }
  return;
}
