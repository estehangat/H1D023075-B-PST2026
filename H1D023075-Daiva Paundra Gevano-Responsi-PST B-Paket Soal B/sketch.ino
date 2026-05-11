#include <Arduino.h>
#include <Servo.h>

Servo myservo;
const int servoPin = 9;

int ledPin = 7;
int btnUp = 2;
int pos = 0;
int val = 0;
bool lastUpState = HIGH;

void setup(){
  pinMode(ledPin, LOW);
  pinMode(btnUp, INPUT_PULLUP);
  myservo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("DRS: CLOSED")
}

void loop(){
  val = analogRead();
  pos = map(val,
             0,
             1023,
             0,
             180); 
  myservo.write(pos);
  bool upState = digitalRead(btnUp);
  if(Serial.available() > 0){
    if(lastUpState == HIGH && upState == LOW){
      digitalWrite(ledPin, HIGH);
      Serial.println("DRS: ACTIVE");
    } else {
      digitalWrite(ledPin, LOW);
      Serial.println("DRS: CLOSED");
    }
    lastUpState = upState;
  }
}
