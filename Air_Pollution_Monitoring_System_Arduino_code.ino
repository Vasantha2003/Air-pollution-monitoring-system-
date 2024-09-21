#include <SoftwareSerial.h>
SoftwareSerial ESP8266(2,3); 
#define MQ2_PIN A0 // Analog pin for MQ2 sensor
#define MQ3_PIN A1 // Analog pin for MQ3 sensor
#define MQ7_PIN A2 // Analog pin for MQ7 sensor
#define VOLTAGE_REFERENCE 5.0 // Voltage reference (in volts)
#define MQ2_RO 5.0 // Sensor resistance in clean air for MQ2 (in kilo ohms)
#define MQ3_RO 20.0 // Sensor resistance in clean air for MQ3 (in kilo ohms)
#define MQ7_RO 10.0 // Sensor resistance in clean air for MQ7 (in kilo ohms)
#define MQ2_CONVERSION_FACTOR 0.01 // PPM per unit of sensor resistance change for MQ2
#define MQ3_CONVERSION_FACTOR 0.01 // PPM per unit of sensor resistance change for MQ3
#define MQ7_CONVERSION_FACTOR 0.01 // PPM per unit of sensor resistance change for MQ7

void setup() {
  Serial.begin(9600); // Initialize serial communication
  ESP8266.begin(115200);
}

void loop() {
  float ppmMQ2 = readPPM(MQ2_PIN, MQ2_RO, MQ2_CONVERSION_FACTOR);
  float ppmMQ3 = readPPM(MQ3_PIN, MQ3_RO, MQ3_CONVERSION_FACTOR);
  float ppmMQ7 = readPPM(MQ7_PIN, MQ7_RO, MQ7_CONVERSION_FACTOR);

  
  ESP8266 .print(ppmMQ2);
  ESP8266 .print(" ");
  ESP8266 .print(ppmMQ3);
  ESP8266 .print(" ");
  ESP8266 .print(ppmMQ7);
  ESP8266 .print("\n");
  

  Serial .print(ppmMQ2);
  Serial .print(" ");
  Serial .print(ppmMQ3);
  Serial .print(" ");
  Serial .print(ppmMQ7);
  Serial .print("\n");
  delay(100); // Delay for stability
}

float readPPM(int pin, float Ro, float conversionFactor) {
  int sensorValue = analogRead(pin); // Read the analog value from sensor
  float voltage = sensorValue * (VOLTAGE_REFERENCE / 1023.0); // Convert analog value to voltage
  float sensorResistance = ((VOLTAGE_REFERENCE - voltage) * Ro) / voltage; // Calculate sensor resistance
  float ppm = sensorResistance * conversionFactor; // Convert sensor resistance to PPM
  return ppm;
}
