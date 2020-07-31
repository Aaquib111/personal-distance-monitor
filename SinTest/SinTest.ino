void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Sine Wave & Cosine Wave
  float angle=0;
  for(angle=0;angle<=90;angle=angle+0.1)
  {
    float sina=sin(angle);
    Serial.print(sina);
    delay(1);
  }
}
