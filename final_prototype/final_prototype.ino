#include <Wire.h>
#include <WireIMXRT.h>
#include <WireKinetis.h>

#include <SparkFun_GridEYE_Arduino_Library.h>

#include <SparkFun_AK975X_Arduino_Library.h>

GridEYE grideye;
AK975X movementSensor;

int ult = 3;
int DISTANCE_THRESHOLD = 2;
double DISTANCE_THRESHOLD_CM;
double IR_THRESHOLD = 20;
int VIB_PIN = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  pinMode(VIB_PIN, OUTPUT);
  pinMode(ult, INPUT);
  grideye.begin();
  //movementSensor.begin();
  //DISTANCE_THRESHOLD_CM = DISTANCE_THRESHOLD * 30.48;
  DISTANCE_THRESHOLD_CM = 100;
}

void loop() {
  double u = ultReading();
  Serial.print("Ultrasonic: ");
  Serial.println(u);
  double h = gridReading();
  Serial.print("IR: ");
  Serial.println(h);
  
  if(u < DISTANCE_THRESHOLD_CM){ 
    Serial.println("Reached 1");
    if(h > IR_THRESHOLD){
      Serial.println("Reached 2");
      vibrate();  
    }
  }
  stopVibrate();
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

double gridReading(){
// variables to store temperature values
  float testPixelValue = 0;
  double hotPixelValue = 0;
  int hotPixelIndex = 0;

  // for each of the 64 pixels, record the temperature and compare it to the 
  // hottest pixel that we've tested. If it's hotter, that becomes the new
  // king of the hill and its index is recorded. At the end of the loop, we 
  // should have the index and temperature of the hottest pixel in the frame
  for(unsigned char i = 0; i < 64; i++){
    testPixelValue = grideye.getPixelTemperature(i);
      if(testPixelValue > hotPixelValue){
        hotPixelValue = testPixelValue;
        hotPixelIndex = i;
      }
  }

  // Print the result in human readable format
  //Serial.print("The hottest pixel is #");
  //Serial.print(hotPixelIndex);
  //Serial.print(" at ");
  return hotPixelValue;
  //Serial.print(hotPixelValue);
  //Serial.println("C");

  // toss in a delay because we don't need to run all out
  //delay(500);
  
}
double ultReading(){
  double sensorValue = pulseIn(ult, HIGH) / 58.0;  
  return sensorValue;
}

void vibrate(){
  digitalWrite(VIB_PIN, HIGH);
  delay(1000);
}

void stopVibrate(){
  digitalWrite(VIB_PIN, LOW);  
}
