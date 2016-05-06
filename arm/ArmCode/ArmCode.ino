#include <Servo.h>

Servo jawServo;

void setup() {
  jawServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  int bendRead1 = analogRead(A0);
  int control;
  
  control = bendRead(bendRead1);
}

int bendRead(int sensorRead){
  int jControl;
  jControl = map(sensorRead, 0, 1023, 45, 175);
  Serial.println(jControl);
  jawServo.write(jControl);
}

