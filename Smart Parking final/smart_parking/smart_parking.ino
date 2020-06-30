#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

Servo myservo;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Password_Lenght 7 // Give enough room for six chars + NULL char

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master1[Password_Lenght] = "123456";
char Master2[Password_Lenght] = "987654";
char Master3[Password_Lenght] = "456789";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
const int place[]={11,12};
byte val[2];
int i=0;
int y=0;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;

byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3}; //connect to the column pinouts of the keypad

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()
{
  myservo.attach(10);
  ServoClose();
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print(" Arduino Door");
  lcd.setCursor(0, 1);
  lcd.print("--Look project--");
  delay(3000);
  lcd.clear();
   for(int i=0;i<2;i++)
   {pinMode(place[i], INPUT);}
}

void loop()
{
  if (door == 0)
  {
    customKey = customKeypad.getKey();

    if (customKey == '#')

    {
      lcd.clear();
      ServoClose();
      lcd.print("  Door is close");
      delay(3000);
      door = 1;
    }
  }

  while(door==1){ Open();}

  lcd.setCursor(0, 0);
  lcd.print("P-L:");

  for( y=0;y<2;y++)
     {      
      val[y]=digitalRead(place[y]);
      if(val[y]==0 )
      {
        lcd.setCursor(14+y, 1);
        lcd.print("F");
        }            
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

void ServoOpen()
{
  for (pos = 90 ; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void ServoClose()
{
  for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void Open()
{
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");
  
  customKey = customKeypad.getKey();
  if (customKey) // makes sure a key is actually pressed, equal to (customKey != NO_KEY)
  {
    Data[data_count] = customKey; // store char into data array
    lcd.setCursor(data_count, 1); // move cursor to show each new char
    lcd.print(Data[data_count]); // print char at said cursor
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if ((!strcmp(Data, Master1))||(!strcmp(Data, Master2))||(!strcmp(Data, Master3))) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.clear();
      ServoOpen();
      lcd.print(" Door is Open");
      delay(5000);
      lcd.clear();
      door = 0;
    }
    else
    {
      lcd.clear();
      lcd.print(" Wrong Password");
      delay(1000);
      door = 1;
    }
    clearData();
  }
}
