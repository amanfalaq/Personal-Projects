#include <Keypad.h>
#include <string.h>
#include <Servo.h>
#include <LiquidCrystal.h>
  const byte ROWS = 4; //four rows
  const byte COLS = 4; //four columns
  char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  { '7','8','9','C'},
  {'*','0','#','D'}
  };
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
String input = "";                //password which we input
String password = "1234";        //the right password
Servo lock;                      //the servo is used as a door
int openPos = 180;                //open position for the door
int closePos = 0;                //close position for the door
int buzzerPin = 11;              //buzzer pin
int attempt = 0;                 //keeps track of the attempts
LiquidCrystal lcd(12, 13, A0, A1, A2, A3);
void setup() {
  Serial.begin(9600);
  lock.attach(10);                //lock is in pin 10
  delay(500);
  lock.write(closePos);           //sets lock as close
  pinMode(buzzerPin,OUTPUT);      //links buzzerpin as output
  lcd.begin(16,2);                //initializes the lcd
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
}
void beep(int duration){          //the beep function 
  digitalWrite(buzzerPin,HIGH);
  delay(duration);
  digitalWrite(buzzerPin,LOW);
}
void clearLine2() {               //function to clear the second line
  lcd.setCursor(0, 1);            //it is used to clear the password attempts 
  lcd.print("                ");  //the user has done
  lcd.setCursor(0, 1);
}
void loop() {
  // put your main code here, to run repeatedly:
  char customKey = customKeypad.getKey();
    if (customKey){
      beep(100);
      if (customKey == '#'){      //checks if enter button(#) is pressed
      lcd.setCursor(0,1);
        if (input == password){
          lcd.clear();
          lcd.print("Access Granted");
          beep(400);
          lock.write(openPos);
          delay(500);
          lock.write(openPos);
          delay(3000);
          lock.write(closePos);
          delay(500);
          lock.write(closePos);
          attempt = 0;            //resets the attempts
        }
        else{
          lcd.clear();
          lcd.print("Access Denied");
          beep(100);
          delay(100);
          beep(100);
          delay(300);
          attempt++;    //for every incorrect attempt, increases tally by 1
            if(attempt >= 3){     //when more than 3 attempts are made, user gets locked out for 5 seconds
              lcd.clear();
              lcd.print("Try Again Later");
              attempt = 0;
              beep(500);
              delay(5000);
            }
        }
        input = "";     
        lcd.clear();
        lcd.print("Enter Password:"); 
        lcd.setCursor(0,1);
      }  
    else{
      input = input + customKey;  //updates the input which comes from the keypad
      lcd.print("*");
    }
  }
}
