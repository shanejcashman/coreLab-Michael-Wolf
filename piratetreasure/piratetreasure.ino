#include <EEPROM.h>
#include <Servo.h>

String myName;
int treasureX, treasureY;
int inputX, inputY;
int nearness;
int nearnessX, nearnessY;
int servoAngle = 1;

const int servoMin = 115;
const int servoMax = 170;

Servo myservo;

int readNum (char *prompt) {
  int inputNum = 0;
  while (inputNum < 1 || inputNum > 9) {
    Serial.println ("All numbers must be between 1 and 9 inclusive!");
    Serial.println(prompt);
    while (Serial.available() == 0) {}
    inputNum = Serial.parseInt();
    Serial.print("You entered: ");
    Serial.print(inputNum);
    Serial.print("\n\n");
  }
  return (inputNum);
}

int findNearness () {
  if (treasureX >= inputX)
    nearnessX = treasureX - inputX;
  else
    nearnessX = inputX - treasureX;

  if (treasureY >= inputY)
    nearnessY = treasureY - inputY;
  else
    nearnessY = inputY - treasureY;

  return (nearnessX + nearnessY);
}

void servoWiggle () {
  for (int i = 0; i < 3; i++) {
    myservo.write(servoMin);
    delay(200);
    myservo.write(170);
    delay(200);
  }
  myservo.write(150);
}

// clear serial terminal
void clearTerminal () {
  for (int i = 3; i > 0; i--) {
    Serial.print("Clearing screen in ");
    Serial.print(i);
    Serial.println(" seconds.");
    delay (1000);
  }
  for (int i = 0; i < 100; i++) {
    Serial.println("");
  }
}

void setup() {
  Serial.begin(9600);
  servoWiggle ();
  myservo.attach(9);
  myservo.write(servoMin);
  tone(11, 200, 500);
  
}

void loop() {
  int toneFreq;
  int toneFreq2;

  inputX = 0;
  inputY = 0;
  servoWiggle();
  Serial.println("Hello Hider.");
  treasureX = readNum("Please enter the X location to hide the treasure:");
  treasureY = readNum("Please enter the Y location to hide the treasure:");
  clearTerminal ();
  Serial.println("The treasure is hidden!\n");

  Serial.println("Seeker.  Enter your name:");
  while (Serial.available() == 0) {}
  myName = Serial.readString();
  Serial.print("Hello ");
  Serial.print(myName);
  Serial.println(".  Good to meet you!\n");


  while (!(treasureX == inputX && treasureY == inputY)) {
    inputX = readNum("Guess the X location of the treasure:");
    inputY = readNum("Guess the Y location of the treasure:");

    Serial.print("Your nearness quotient is: ");
    Serial.print(findNearness());
    Serial.println(",\n");
    
    if (inputX == treasureX) {
      Serial.print('\n');
      Serial.println("ARGH! X marks the spot. Your X coordinate is correct!");
      Serial.print('\n');
      tone(11, 2000, 300);
      delay(500);
      tone(11, 3000, 300);
      delay(750);
      tone (11, 2000, 300);
      delay(500);
    }

    if (inputY == treasureY) {
      Serial.print('\n');
      Serial.println("Ye saved the crew with the correct Y coordinate");
      Serial.print('\n');
      tone(11, 3000, 300);
      delay(500);
      tone(11, 2000, 300);
      delay (750);
      tone(11, 3000, 300);
      delay(500);
    }
    
    toneFreq = map (findNearness(), 0, 16, 1000, 40);
    toneFreq2 = map (findNearness(), 5, 100, 300, 10);
    tone(21, toneFreq, 100);
    delay (300);
    tone(31, toneFreq, 250);
    tone(11, toneFreq2, 100);
    servoAngle = map (findNearness(), 0, 16, servoMax, servoMin);
    myservo.write(servoAngle);
  }

  tone(11, 1000, 100);
  delay (100);
  tone(11, 1500, 205);
  delay (10);
  tone(11, 3000, 250);
  delay (1000);
  tone(11, 200, 2000);
  delay(200);

  Serial.println("You Won!\n\n\nRestarting:");
  servoWiggle();
  delay

}
