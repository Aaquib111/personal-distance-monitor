#include <curveFitting.h>

#include <SparkFunMLX90614.h>
#include <Wire.h>


const int order = 3;

double data[] = {3.616, 2.2915, 1.6229, 1.1249, 1.0956, 0.9035}; // difference data
double x[] = {1,2,3,4,5,6};
double testx[] = {0,1,2,3,4,5};
double testy[] = {0,1,4,9,16,25};

int ret;
double coeffs[4];


void setup() {
  Serial.begin(9600);

  //int ret = fitCurve(order, sizeof(data), t, data, sizeof(coeffs), coeffs);
  //ret = fitCurve(order, sizeof(testy)/4, testx, testy, sizeof(coeffs)/4, coeffs);
  
  ret = fitCurve(order, sizeof(data)/4, data, x, sizeof(coeffs)/4, coeffs);
  if (ret == 0){ //Returned value is 0 if no error
    Serial.print("Coefficients are: ");
    for (int i = 0; i < sizeof(coeffs)/4; i++){
        Serial.println(coeffs[i]);
    }
  }else{
    Serial.println("Regression returned error");  
  }
}

void loop() {
  if(ret != 0){
    Serial.print("Something went wrong: ");  
    Serial.println(sizeof(data));
  }
  Serial.println("Coeffs: ");
  Serial.print("A: ");
  Serial.println(coeffs[0]);
  Serial.print("B: ");
  Serial.println(coeffs[1]);
  Serial.print("C: ");
  Serial.println(coeffs[2]);
  Serial.print("D: ");
  Serial.println(coeffs[3]);
  Serial.println("------------------------------------");
}
