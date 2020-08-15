#include "EloquentTinyML.h"
#include<TensorFlowLite.h>





#include "temperature_predictor.h"
#include "humidity_predictor.h"
#include "DHT.h"
float prevtemp;
float prevhum;
#define DHTPIN 4
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
#define NUMBER_OF_INPUTS 8
#define NUMBER_OF_OUTPUTS 1

#define TENSOR_ARENA_SIZE 2*1024


Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> temprature(temperature_predictor_tflite);
Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, 3 * 1024> humidity(humidity_predictor_tflite);

void setup() {
  Serial.begin(115200);

  dht.begin();
}

void loop() {
  // pick up a random x and predict its sine
  float h = dht.readHumidity();
  float t = dht.readTemperature(true);

  delay(1000);

   

  if (isnan(h) || isnan(t) ) {    
    Serial.println(F("Failed to read from DHT sensor!"));
    float input_array[8] = {2020, 5, 26, 11,  30, 0,  prevtemp,  prevhum};
    float input_array2[8] = {2020 , 2, 4, 6,  40, 0,  prevhum,  prevtemp}; 
    
    float hum = humidity.predict( input_array2);
    float temp = temprature.predict( input_array);


    Serial.print("\t predicted humidity: ");
    Serial.println(hum);
    Serial.print("\t predicted temp: ");
    Serial.println(temp);
    delay(1000);
    return;
  }
  else
  { Serial.print("\t humidity: ");
    Serial.println(h);
    Serial.print("\t  temp: ");
    Serial.println(t);
    prevtemp = t;
    prevhum = h;

  }


}
