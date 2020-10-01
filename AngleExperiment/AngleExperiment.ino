#include <SparkFunMLX90614.h>
#include <Wire.h>

IRTherm therm; //Infrared sensor object

int distance = 0;
int angle = 0;

void setup() {
  Serial.begin(9600);
  therm.begin();
  therm.setUnit(TEMP_F);
  Serial.println("Angle,Distance,ObjTemp,AmbTemp");
}

void loop() {
  while(Serial.available()){
    String s = Serial.readString();
    angle = s.substring(0,2).toInt();
    distance = s.substring(2).toInt();
    for(int i = 0; i<100; i++){
      infraredReading();
      delay(10);  
    }
  }
}



//READING IR SENSOR OUTPUT
void infraredReading(){
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    Serial.print(angle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    Serial.print(therm.object());
    Serial.print(",");
    Serial.println(therm.ambient());

  }else{
    //Serial.println("Signal not found, check IR connections...");
  }
}
