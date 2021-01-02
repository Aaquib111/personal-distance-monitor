
int ult = 4;
int a = 0.20;
int prevRange;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ult, INPUT);
  prevRange = pulseIn(ult, HIGH) / 58.0;
}

void loop() {
  int sensorValue = pulseIn(ult, HIGH) / 58.0;
  int sensorValue2 = (1-a)*prevRange + a*sensorValue;
  prevRange = sensorValue;
  Serial.print(sensorValue);      //the first variable for plotting
  Serial.print(",");              //seperator
  Serial.println(sensorValue2); 
  delay(200);
}
