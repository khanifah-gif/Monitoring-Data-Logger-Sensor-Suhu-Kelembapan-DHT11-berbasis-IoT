#define BLYNK_PRINT Serial

//Copas dari "Device Info" di Blynk web
#define BLYNK_TEMPLATE_ID "TMPLz_ExWeVq"
#define BLYNK_DEVICE_NAME "Monitoring Suhu Kelembapan Blynk"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "TRIGGER_WIFI.h"               
#include "TRIGGER_GOOGLESHEETS.h"
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_pin D5
DHT dht (dht_pin, DHTTYPE);
int Pendingin = D3;

char auth[] = "";         //Copas dari "Device Info" di Blynk web
char ssid[] = "";         //nama wifi
char pass[] = "";         //password wifi

/**********Google Sheets Definations***********/
char column_name_in_sheets[ ][20] = {"value1","value2"};
String Sheets_GAS_ID = "AKfycbzG0SdWAqpZqZAeBTeghLeQMQSj1ou2g8RpiIqN2PrOrJu8QqKxd4_mRObogY-TS_4W";
int No_of_Parameters = 2;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  dht.begin();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );

}

void loop() {
  float s = dht.readTemperature();
  float h = dht.readHumidity();

  if(s > 25){
    digitalWrite(Pendingin,HIGH);
   }
  else{digitalWrite(Pendingin,LOW);}

  Data_to_Sheets(No_of_Parameters,  s,  h);

  Serial.print("Suhu :");
  Serial.print(s);
  Serial.print(",");
  Serial.print("Kelembapan : ");
  Serial.print(h);
  Serial.print("\n");
  delay(500);

  //kirim ke Blynk
  Blynk.virtualWrite(V0, s);
  Blynk.virtualWrite(V1, h);
  delay(500);

}
