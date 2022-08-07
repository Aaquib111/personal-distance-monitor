#include <TFMPlus.h>
#include <SoftwareSerial.h>
  
int dist;
int strength;
int temp;



TFMPlus tf;  
SoftwareSerial Serial2(12, 13);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(20);
  Serial2.begin(115200); 
  delay(20); 

  tf.begin( &Serial2);
}

void loop() {
  delay(50);   // Loop delay to match the 20Hz data frame rate

    if( tf.getData( dist, strength, temp)) // Get data from the device.
    {
      Serial.print("Distance: ");
      Serial.print(dist);
      Serial.print(",");
      Serial.print("Strength: ");
      Serial.print(strength);
      Serial.print(",");
      Serial.print("Temp: ");
      Serial.println(temp);
    }
    else                  // If the command fails...
    {
      //tf.printFrame();  // display the error and HEX dataa
    }

}
