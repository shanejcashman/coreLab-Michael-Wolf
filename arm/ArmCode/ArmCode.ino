#include <Servo.h>

Servo armServo;
Servo baseServo;

int aControl = 95;
int bControl = 95;

void setup() {
  armServo.attach(9);
  baseServo.attach(10);
  Serial.begin(9600);
}

void loop() {
  aControl = analogRead(A0);
  bControl = analogRead(A1);
  
  aControl = map(aControl, 0, 1023, 60, 120);
  bControl = map(bControl, 0, 1023, 60, 120);

  Serial.println(aControl);
  Serial.println(bControl);

  if (aControl < 99 && aControl > 91) {
    aControl == 95;
  } else {
    armServo.write(aControl);
  }
  if (bControl < 99 && aControl > 91) {
    bControl == 95;
  } else {
    baseServo.write(bControl);
  }
}
