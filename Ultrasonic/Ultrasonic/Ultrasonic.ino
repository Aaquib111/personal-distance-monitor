
int readPin = A4;
int trigger = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(21);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(21);
  Serial.println("Reached Here");
}

void loop() {
  //if(Serial.available() == 0) Serial.println("N");
  //while(Serial.available() > 0){
  //  int b = Serial.read();
  //  Serial.println(b);
  //}
  digitalWrite(trigger, LOW);
  delayMicroseconds(21);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(21);
  int i = analogRead(readPin);
  Serial.println(i);
}
