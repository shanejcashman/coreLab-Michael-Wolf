void setup() {
  Serial.begin(9600);
  
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop() {
  int xRead = analogRead(A0);
  int yRead = analogRead(A1);
  int zRead = analogRead(A2);

  map(xRead, 300, 400, 0, 255);
  map(yRead, 300, 400, 0, 255);
  map(zRead, 300, 400, 0, 255);

  constrain(xRead, 0, 255);
  constrain(yRead, 0, 255);
  constrain(zRead, 0, 255);
  
  analogWrite(3, xRead);
  analogWrite(5, yRead);
  analogWrite(6, zRead);

  Serial.print(xRead);
  Serial.print(" ");
  Serial.print(yRead);
  Serial.print(" ");
  Serial.print(zRead);
  Serial.print("\n");
}
