#include <SparkFunMLX90614.h>
#include <Wire.h>
#define ledPin 7
int state = 0;
int increment = 0;

const int VIB_MOTOR_PIN = 11;

IRTherm therm; //Infrared sensor object

void ledOff() {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  //Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
}

void ledOn() {
  digitalWrite(ledPin, HIGH);
  //Serial.println("LED: ON");
}

void takeTemp() {
  double temp;
  if (therm.read()) {
    temp = therm.object();
    //Serial.print(therm.object());
    //Serial.println(therm.ambient());
  } else {
    temp = 0.0;
  }
  Serial.print(increment);
  Serial.print(",");
  Serial.println(temp);
  increment = increment + 1;
}

void vibrateMotor() {
  digitalWrite(VIB_MOTOR_PIN, HIGH);
  delay(1000);
  digitalWrite(VIB_MOTOR_PIN, LOW);
}
void (*functptr[])() = {ledOff, ledOn, takeTemp, vibrateMotor};

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // Default communication rate of the Bluetooth module

  therm.begin();
  therm.setUnit(TEMP_F);

  pinMode(VIB_MOTOR_PIN, OUTPUT);
}
void loop() {
  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
    Serial.println(state);
    (*functptr[state])();
    state = 0;
  }
}
