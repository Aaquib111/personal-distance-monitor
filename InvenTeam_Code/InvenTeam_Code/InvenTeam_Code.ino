#include <SparkFunMLX90614.h>
#include <Wire.h>

IRTherm therm; //Infrared sensor object

//volatile int pwm_value = 0; //PWM signal value
//volatile int prev_time = 0; //Value of the previous time before falling edge of PWM signal

const int delay_ = 500; //Delay loop value, constant for now, in milliseconds
const int PWM_PIN = 4; //PWM pin

void setup() {
  Serial.begin(9600);
  therm.begin();
  therm.setUnit(TEMP_F);
  pinMode(PWM_PIN, INPUT);
}

void loop() {
  //READING IR SENSOR OUTPUT
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
    // temperatures.
    // They'll be floats, calculated out to the unit you set with setUnit().
    Serial.print("Object: " + String(therm.object(), 2));
    Serial.println("F");
    Serial.print("Ambient: " + String(therm.ambient(), 2));
    Serial.println("F");
  }else{
    Serial.println("Signal not found, check IR connections...");
  }
  
  //READING RANGEFINDER OUTPUT
  int val = pulseIn(PWM_PIN, HIGH);
  Serial.println(val);

  Serial.println("---------------------------------------"); //Separates loops from each other
  
  //attachInterrupt(0, rising, RISING);
  delay(delay_);
}

/*void rising(){
  attachInterrupt(0, falling, FALLING);
  prev_time = micros();
}

void falling() {
  attachInterrupt(0, rising, RISING);
  pwm_value = micros()-prev_time;
  Serial.println("PWM Value: " + pwm_value);
  Serial.println("---------------------------------------");
}*/
