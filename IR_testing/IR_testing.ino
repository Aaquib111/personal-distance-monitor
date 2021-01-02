#include <SparkFun_AK975X_Arduino_Library.h>
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <SparkFunMLX90614.h>
#include <SparkFun_ADS1015_Arduino_Library.h>
#include <Wire.h>

IRTherm therm; //Infrared sensor object

ADS1015 irsensor;                   //Initialize using ADS1015 library
float multiplier;

GridEYE grideye;

AK975X movementSensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(2000);
  
  therm.begin();
  therm.setUnit(TEMP_F);

  if(irsensor.begin() == false){
    Serial.println("Device not found. Check wiring, then restart.");
    while(1);
  }else{
    Serial.println("Started.");  
  }
  multiplier = irsensor.getMultiplier();

  grideye.begin(); //needs 115200
  
  if (movementSensor.begin() == false)
  {
    Serial.println("Device not found. Check wiring.");
    while (1);
  }
}

void loop() {
  infraredReading();
  delay(100);
}
 

//READING IR SENSOR OUTPUT
void infraredReading(){
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    //Serial.print("Object temp:");
    Serial.print(therm.object());
    //Serial.print(",");
    //Serial.print("Ambient temp:");
    //Serial.println(therm.ambient());
  }else{
    Serial.println("Signal not found, check IR connections...");
  }
}

void sparkXReading(){
  int data;
  data = irsensor.getAnalogData(0);   //Retrieve raw data value from sensor
  //Serial.print("ADC input voltage: ");
  Serial.println(data * multiplier);
  //Serial.println("mV");
}

void gridReading(){
  //returns hottest pixel
  float testPixelValue = 0;
  float hotPixelValue = 0;
   for(unsigned char i = 0; i < 64; i++){
    testPixelValue = grideye.getPixelTemperature(i);
      if(testPixelValue > hotPixelValue){
        hotPixelValue = testPixelValue;
      }
  }
  Serial.println(hotPixelValue);
}

void humanReading(){
  //returns hottest value
  if (movementSensor.available())
  {
    int ir1 = movementSensor.getIR1();
    int ir2 = movementSensor.getIR2();
    int ir3 = movementSensor.getIR3();
    int ir4 = movementSensor.getIR4();
    int m = max(ir1, max(ir2, max(ir3, ir4)));
    movementSensor.refresh();
    Serial.println(m);
  }
  
}
