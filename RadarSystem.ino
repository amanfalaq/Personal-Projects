#include <Servo.h>

Servo myServo;

int trigPin = 10;
int echoPin = 11;

long duration;
int distance;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(9);
}

void loop() {

  // Sweep 0 → 180
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(20);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }

  // Sweep 180 → 0
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(20);

    distance = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}

int getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return 0;

  return duration * 0.034 / 2;
}