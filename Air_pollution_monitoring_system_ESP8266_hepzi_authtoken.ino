#define BLYNK_TEMPLATE_ID "TMPL38FXaFzoc"
#define BLYNK_TEMPLATE_NAME "Air Pollution Monitoring System"
#define BLYNK_AUTH_TOKEN "G85_-lvDyD9bV73Vr22FdTQx5wmadBY7"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<SoftwareSerial.h>

#define tx_pin D2
#define rx_pin D3

SoftwareSerial arduinoSerial(tx_pin,rx_pin);

int buzzer=5;

float mq2,mq3,mq7 = 0;

char ssid[] = "Thanis Hepziba Mary";  
char pass[] = "hepzibam2003";

BlynkTimer timer;

void setup()
{
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
Serial.begin(9600);
arduinoSerial.begin(115200);
pinMode(buzzer,OUTPUT);
timer.setInterval(1000L,myTimer);

}
void loop()
{
    timer.run();
    Blynk.run();
}
void myTimer()
{
  if (arduinoSerial.available() > 0) {
    char inputString[100];
    arduinoSerial.readBytesUntil('\n', inputString, sizeof(inputString));

    char *token = strtok(inputString, " \n");

    if (token != NULL) {
      mq2 = atof(token);
      token = strtok(NULL, " \n");
    }

    if (token != NULL) {
      mq3 = atof(token);
      token = strtok(NULL, " \n");
    }


    if (token != NULL) {
      mq7 = atof(token);
    }

  Serial .print(mq2);
  Serial .print(" ");
  Serial .print(mq3);
  Serial .print(" ");
  Serial .print(mq7);
  Serial .print("\n");
  

     Blynk.virtualWrite(V1,mq2);
     Blynk.virtualWrite(V2,mq3);
     Blynk.virtualWrite(V3,mq7);
  }
  
  
 
}


  
  
