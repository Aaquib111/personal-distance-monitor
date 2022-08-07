#include <ExponentialRegression.h>
#include <LinearRegression.h>
#include <LogarithmicRegression.h>
#include <LogisticRegression.h>
#include <PotentialRegression.h>

const int order = 3;

double data[] = {3.616, 2.2915, 1.6229, 1.1249, 1.0956, 0.9035}; // difference data
double distance[] = {1,2,3,4,5,6};
double testx[] = {0,1,2,3,4,5};
double testy[] = {0,1,4,9,16,25};

int ret;
double coeffs[4];

PotentialRegression pr = PotentialRegression();
double values[2];

void setup() {
  Serial.begin(9600);
  Serial.println("Begin learn");
  for(int i = 0; i < sizeof(data)/sizeof(double); i++){
      pr.learn(data[i], distance[i]);
  }
  Serial.println("End learn");
  delay(1000);
  showValues();
}

void loop() {
  for(int i = 0; i < 6; i++){
        Serial.print("Result (");
        Serial.print(data[i]);
        Serial.print("): ");
        Serial.println(pr.calculate(data[i])); 
  }
  delay(5000);
}

void showValues(){
  Serial.print("Values: ");
  pr.parameters(values);
  Serial.print("Y = ");
  Serial.print(values[0]);
  Serial.print("*e ^");
  Serial.print(values[1]); 
  Serial.println("* X"); 
 }
