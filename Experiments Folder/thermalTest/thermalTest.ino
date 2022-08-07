#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>

GridEYE grideye;

void setup() {

  // Start your preferred I2C object 
  Wire.begin();
  // Library assumes "Wire" for I2C but you can pass something else with begin() if you like
  grideye.begin();
  // Pour a bowl of serial
  Serial.begin(115200);

}

void loop() {

  Serial.print("Thermistor Temperature in Celsius: ");
  Serial.println(grideye.getDeviceTemperature());
  Serial.print("Thermistor Temperature in Fahrenheit: ");
  Serial.println(grideye.getDeviceTemperatureFahrenheit());
  Serial.print("Thermistor Temperature register contents: ");
  Serial.println(grideye.getDeviceTemperatureRaw(), BIN);

  Serial.println();
  Serial.println();

  delay(1000);
  
}
