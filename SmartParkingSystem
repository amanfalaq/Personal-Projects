#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Pins
const int echoPin = 13;
const int trigPin = 12;
const int buzzer = 11;
const int greenLED = 10;
const int yellowLED = 9;
const int redLED = 8;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  int beepDelay = map(distance, 10, 40, 50, 500);

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  if (distance > 40) {
    lcd.setCursor(0, 1);
    digitalWrite(greenLED, HIGH);
    lcd.print("SAFE        ");
    noTone(buzzer);
  } 
  else if (distance > 20) {
    lcd.setCursor(0, 1);
    lcd.print("SLOW DOWN     ");
    digitalWrite(yellowLED, HIGH);
    
    tone(buzzer, 1000);
    delay(beepDelay);
    noTone(buzzer);
    delay(beepDelay);
  } 
    else if (distance > 10) {
    lcd.setCursor(0, 1);
    lcd.print("CAUTION     ");
    digitalWrite(redLED, HIGH);
    
    tone(buzzer, 1000);
    delay(beepDelay);
    noTone(buzzer);
    delay(beepDelay);
    }
  else {
    lcd.setCursor(0, 1);
    lcd.print("STOP        ");
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH);
    
    tone(buzzer, 1000);
  }
}
