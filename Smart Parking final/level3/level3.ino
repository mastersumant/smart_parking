#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo myservo;

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define Password_Lenght 4 // Give enough room for six chars + NULL char

int pos = 0;    // variable to store the servo position

char Data[Password_Lenght]; // 6 is the number of chars it can hold + the null char = 7
char Master1[Password_Lenght] = "444";
char Master2[Password_Lenght] = "443";
char Master3[Password_Lenght] = "449";
char Master4[Password_Lenght] = "333";
char Master5[Password_Lenght] = "334";
char Master6[Password_Lenght] = "339";
char Master7[Password_Lenght] = "994";
char Master8[Password_Lenght] = "999";
char Master9[Password_Lenght] = "993";
char Master10[Password_Lenght] = "344";
char Master11[Password_Lenght] = "944";
char Master12[Password_Lenght] = "433";
char Master13[Password_Lenght] = "933";
char Master14[Password_Lenght] = "499";
char Master15[Password_Lenght] = "399";
char Master16[Password_Lenght] = "434";
char Master17[Password_Lenght] = "494";
char Master18[Password_Lenght] = "343";
char Master19[Password_Lenght] = "393";
char Master20[Password_Lenght] = "949";
char Master21[Password_Lenght] = "939";
char Master22[Password_Lenght] = "943";
char Master23[Password_Lenght] = "439";
char Master24[Password_Lenght] = "349";
char Master25[Password_Lenght] = "493";
char Master26[Password_Lenght] = "394";
char Master27[Password_Lenght] = "934";
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;
const int place[]={11,12,13};
byte val[2];
int i=0;
int y=0;
int count=0;
#define exit 2
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
bool door = true;

byte colPins[COLS] = {5,4,3};
byte rowPins[ROWS] = {9,8,7,6};

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad

void setup()
{

  myservo.attach(10);
  ServoClose();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.print(" SMART PARKING ");
  lcd.setCursor(0, 1);
  lcd.print("SIT,TUMKUR");
  delay(3000);
  lcd.clear();
   for(int i=0;i<=2;i++)
   {pinMode(place[i], INPUT);}
   pinMode(exit,INPUT);
  
}

void loop()
{
   
        Open();
  if((digitalRead(place[0])==0)&&(digitalRead(place[1])==0)&&(digitalRead(place[2])==0))
  {
    lcd.setCursor(0,0);
    lcd.print("-----FULL-----");
    while((digitalRead(place[0])==0)&&(digitalRead(place[1])==0)&&(digitalRead(place[2])==0))
    {
      lcd.setCursor(13, 1);
      lcd.print("FFF");
    }
    }
    
if(digitalRead(exit)==0)
{
  ServoOpen();
  delay(2000);
  ServoClose();
}
if(digitalRead(place[0])==0)
{
lcd.setCursor(13, 1);
lcd.print("F");
}
else
{
lcd.setCursor(13, 1);
lcd.print("E");
}
if(digitalRead(place[1])==0)
{
lcd.setCursor(14, 1);
lcd.print("F");}
else
{
lcd.setCursor(14, 1);
lcd.print("E");}
if(digitalRead(place[2])==0)
{
lcd.setCursor(15, 1);
lcd.print("F");}
else
{
lcd.setCursor(15, 1);
lcd.print("E");}
             
     
  
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
  for (pos = 90 ; pos >= 20; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void ServoClose()
{
  for (pos = 20; pos <= 90; pos += 1) { // goes from 180 degrees to 0 degrees
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
    //lcd.print(Data[data_count]); // print char at said cursor
    lcd.print("*");
    data_count++; // increment data array by 1 to store new char, also keep track of the number of chars entered
  }

  if (data_count == Password_Lenght - 1) // if the array index is equal to the number of expected chars, compare data to master
  {
    if ((!strcmp(Data, Master1))||(!strcmp(Data, Master2))||(!strcmp(Data, Master3))||(!strcmp(Data, Master4))||(!strcmp(Data, Master5))||(!strcmp(Data, Master6))||(!strcmp(Data, Master7))||(!strcmp(Data, Master8))||(!strcmp(Data, Master9))||(!strcmp(Data, Master10))||(!strcmp(Data, Master11))||(!strcmp(Data, Master12))||(!strcmp(Data, Master13))||(!strcmp(Data, Master14))||(!strcmp(Data, Master15))||(!strcmp(Data, Master16))||(!strcmp(Data, Master17))||(!strcmp(Data, Master18))||(!strcmp(Data, Master19))||(!strcmp(Data, Master20))||(!strcmp(Data, Master21))||(!strcmp(Data, Master22))||(!strcmp(Data, Master23))||(!strcmp(Data, Master24))||(!strcmp(Data, Master25))||(!strcmp(Data, Master26))||(!strcmp(Data, Master27))) // equal to (strcmp(Data, Master) == 0)
    {
      lcd.clear();
      ServoOpen();
      lcd.print(" Door is Open");
      delay(5000);
      ServoClose();
     
      door = 0;
      count++;
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
