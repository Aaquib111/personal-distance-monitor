#include <Wire.h>
#include <WireIMXRT.h>
#include <WireKinetis.h>

#include <SparkFun_GridEYE_Arduino_Library.h>

#include <SparkFun_AK975X_Arduino_Library.h>

GridEYE grideye;
AK975X movementSensor;

int ult = 5;
int DISTANCE_THRESHOLD = 4;
double DISTANCE_THRESHOLD_CM;
double IR_THRESHOLD = 400;
int VIB_PIN = 11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  delay(2000);

  pinMode(VIB_PIN, OUTPUT);
  pinMode(ult, INPUT);
  
  movementSensor.begin();
  DISTANCE_THRESHOLD_CM = DISTANCE_THRESHOLD * 30.48;
}

void loop() {
  double u = ultReading();
  Serial.print("Ultrasonic: ");
  Serial.println(u);
  double h = humanReading();
  Serial.print("IR: ");
  Serial.println(h);
  
  if(u < DISTANCE_THRESHOLD_CM){ 
    if(h > IR_THRESHOLD){
      vibrate();  
    }
  }
  
  delay(1000);
}

double humanReading(){
  //returns hottest value
  double m;
  if (movementSensor.available())
  {
    int ir1 = movementSensor.getIR1();
    int ir2 = movementSensor.getIR2();
    int ir3 = movementSensor.getIR3();
    int ir4 = movementSensor.getIR4();
    m = max(ir1, max(ir2, max(ir3, ir4)));
    movementSensor.refresh();
  }
  return m;
}

double ultReading(){
  double sensorValue = pulseIn(ult, HIGH) / 58.0;  
  return sensorValue;
}

void vibrate(){
  //digitalWrite(VIB_PIN, HIGH);
  delay(100);
}
