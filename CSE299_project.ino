#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#define FIREBASE_HOST "ringit-8cebd.firebaseio.com"
#define FIREBASE_AUTH "MrgyfqCe6cE8HE5DLTE76mJmJjvYycUVKeRIPrWm"
#define WIFI_SSID "POKEMON"
#define WIFI_PASSWORD "futuredream2020"

const int analogInPin = A0;
int sensorValue = 0;
int avgValue;
int buf[10], temp;


void setup() {
  Serial.begin(9600);
 
  // connect to wifi.

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 

}

void loop() {
    for(int i=0; i<10; i++)
    {
        buf[i] = analogRead(analogInPin);
        //Serial.println(buf[i]);
        delay(10);
      }
    for(int i=0; i<9; i++)
    {
        for(int j=i+1; j<10; j++)
        {
            if(buf[i] > buf[j])
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
              }
          }
      }
      
      avgValue =0;
      for(int i=2; i<8; i++)
      {
          avgValue += buf[i];
        }
        float pHVoltage = (float)avgValue*5.0/1024/6; 
        float pHValue = -2.826*pHVoltage + 21.34 ;
        //Serial.print("Avg_AnalogInput=");
        //Serial.println(avgValue);
        //Serial.print("Cal_pHVoltage=");
        //Serial.println(pHVoltage);
        Serial.print("pH=");
        Serial.println(pHValue);
        //Firebase.setFloat("voltage",pHVoltage);
        Firebase.setFloat("pH",pHValue); 
        delay(20);
}
