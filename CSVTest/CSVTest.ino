#include <SparkFunMLX90614.h>
#include <Wire.h>

IRTherm therm; //Infrared sensor object

const int delay_ = 10; //Delay loop value, constant for now, in milliseconds

const int PWM_PIN = 4; //PWM pin
const int NUM_READINGS = 5; //Constant number of readings, increase to increase ultrasonic accuracy at the cost of time
int range_readings[NUM_READINGS]; //Array to hold rangefinder reading values
long startTime = 0; //Start time value for range readings
long endTime = 0; //End time value for range readings
int DISTANCE = 5;

const int VIB_MOTOR_PIN = 7;

void setup() {
  Serial.begin(9600);
  therm.begin();
  therm.setUnit(TEMP_F);
  pinMode(PWM_PIN, INPUT);
  pinMode(VIB_MOTOR_PIN, OUTPUT);
  Serial.println("Distance,ObjTemp,AmbTemp");
}

void loop() {
  while(Serial.available()){
    DISTANCE = (Serial.read()-'0');  
    for(int i = 0; i<100; i++){
      infraredReading();  
    }
  }
  
  //Take IR reading and print it
  //infraredReading();
  //Take Ultrasonic reading and print it
  //ultrasonicReading();
  
  //if(therm.object() > 90.00){
  //  vibrateMotor(2);
  //}
   
  //Serial.println("---------------------------------------"); //Separates loops from each other
  delay(delay_);
}

//Function to swap two array elements
void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
// A function to implement bubble sort  
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1])  
            swap(&arr[j], &arr[j+1]);  
}  

//READING RANGEFINDER OUTPUT USING MEDIAN FILTER
void ultrasonicReading(){
  startTime = micros();
  for(int i = 0; i<NUM_READINGS; i++){
      range_readings[i] = pulseIn(PWM_PIN, HIGH);
  }
  endTime = micros();
  Serial.print("Time taken for range readings: ");
  Serial.println(endTime-startTime);
  
  //SORT READINGS
  bubbleSort(range_readings, NUM_READINGS);
  
  //MEDIAN VALUE
  int val = range_readings[NUM_READINGS /2];
  
  Serial.print("Ultrasonic reading: ");
  Serial.println(val);
  
}

//READING IR SENSOR OUTPUT
void infraredReading(){
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    // Use the object() and ambient() functions to grab the object and ambient
    // temperatures.
    // They'll be floats, calculated out to the unit you set with setUnit().
    //Serial.print("Object temp: " + String(therm.object(), 2));
    //Serial.print("Object temp:");
    Serial.print(DISTANCE);
    Serial.print(",");
    Serial.print(therm.object());
    Serial.print(",");
    //Serial.print("Ambient temp:");
    Serial.println(therm.ambient());
    //Serial.println("F");
    //Serial.print("Ambient temp: " + String(therm.ambient(), 2));
    //Serial.println("F");
  }else{
    //Serial.println("Signal not found, check IR connections...");
  }
}

void vibrateMotor(int seconds){
    digitalWrite(VIB_MOTOR_PIN, HIGH);
    delay(seconds * 1000);
    digitalWrite(VIB_MOTOR_PIN, LOW);
}
