int xRead;
int yRead;
int zRead;

void setup() {
  Serial.begin(9600);
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop() {
  xRead = analogRead(A0);
  yRead = analogRead(A1);
  zRead = analogRead(A2);

  map(xRead, 320, 550, 0, 255);
  map(yRead, 320, 550, 0, 255);
  map(zRead, 320, 550, 0, 255);

  analogWrite(3, xRead);
  analogWrite(5, yRead);
  analogWrite(6, zRead);
}
