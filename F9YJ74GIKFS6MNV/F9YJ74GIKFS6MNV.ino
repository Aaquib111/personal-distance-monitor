/*
 * This code was Created by Jonathan Pereira on 10th February 2016 and is in the public domain.
 * Comment the type of wave that you do not wish to generate.
*/

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A4, INPUT_PULLUP);
}

void loop() 
{
    int val = analogRead(A4);
    float convert = val / 5.0;
    Serial.println(convert); 
}
