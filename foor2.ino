                                                                                                             /**
   BasicHTTPSClient.ino

    Created on: 20.08.2018

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
//5A 12 CA B5 35 69 04 81 E6 1F 8A 3D BA F1 87 1A 24 A5 40 64
// Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
const uint8_t fingerprint[20] = {0x5A, 0x12, 0xCA, 0xB5, 0x35, 0x69, 0x04, 0x81, 0xE6, 0x1F, 0x8A, 0x3D, 0xBA, 0xF1, 0x87, 0x1A, 0x24, 0xA5, 0x40, 0x64};

ESP8266WiFiMulti WiFiMulti;

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, INPUT);
  
  Serial.begin(115200);
  
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("TLU", "");
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
}
 int cycle = 0;
 int i = 0;
void loop() {
  // wait for WiFi connection
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    // client->setInsecure();
    HTTPClient https;
    HTTPClient http;
    int value1 = digitalRead(D5);

    if (http.begin(*client, "https://asjade-internet-tanel-default-rtdb.europe-west1.firebasedatabase.app/cycle.json")){
    http.addHeader("Content-Type", "application/json");
    int httpCode2 = http.GET();
    if (httpCode2 > 0) {
        if (httpCode2 == HTTP_CODE_OK || httpCode2 == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, payload);
          Serial.println(doc["cycle"]);
        
          Serial.println(value1);
          if(payload == "0") {
            lampsOff();
            digitalWrite(D4, HIGH);
            digitalWrite(D1, HIGH);
            delay(8000);
            digitalWrite(D4, LOW);
            delay(500);
            digitalWrite(D4, HIGH);
            delay(500);
            digitalWrite(D4, LOW);
            delay(500);
            digitalWrite(D4, HIGH);
            delay(500);
            digitalWrite(D4, LOW);
            delay(200);
            digitalWrite(D3, HIGH);
            delay(800);
            digitalWrite(D3, LOW);
            digitalWrite(D2, HIGH);
            delay(1000);
            digitalWrite(D1, LOW);
            digitalWrite(D0, HIGH);
            delay(4000);
            digitalWrite(D0, LOW);
            delay(500);
            digitalWrite(D0, HIGH);
            delay(500);
            digitalWrite(D0, LOW);
            delay(500);
            digitalWrite(D0, HIGH);
            delay(500);
            digitalWrite(D0, LOW);
            digitalWrite(D1, HIGH);
            delay(1000);
            digitalWrite(D3, HIGH);
            delay(1000);
            digitalWrite(D2, LOW);
            digitalWrite(D3, LOW);
            digitalWrite(D4, HIGH);
          }
          // D4 ROHELINE AUTO
          // D3 KOLLANE AUTO
          // D2 PUNANE AUTO
          // D1 PUNANE KÄIJA
          // D0 ROHELINE KÄIJA
          if(payload == "1"){
            lampsOff();
            digitalWrite(D4, HIGH);
            digitalWrite(D1, HIGH);
            if(value1 == 1){
              delay(1000);
              digitalWrite(D4, LOW);
              delay(500);
              digitalWrite(D4, HIGH);
              delay(500);
              digitalWrite(D4, LOW);
              delay(500);
              digitalWrite(D4, HIGH);
              delay(500);
              digitalWrite(D4, LOW);
              delay(500);
              digitalWrite(D4, HIGH);
              delay(500);
              digitalWrite(D4, LOW);
              delay(100);
              digitalWrite(D3, HIGH);
              delay(800);
              digitalWrite(D3, LOW);
              digitalWrite(D2, HIGH);
              delay(1200);
              digitalWrite(D1, LOW);
              digitalWrite(D0, HIGH);
              delay(8000);
              digitalWrite(D0, LOW);
              delay(500);
              digitalWrite(D0, HIGH);
              delay(500);
              digitalWrite(D0, LOW);
              delay(500);
              digitalWrite(D0, HIGH);
              delay(500);
              digitalWrite(D0, LOW);
              delay(500);
              digitalWrite(D0, HIGH);
              delay(500);
              digitalWrite(D0, LOW);
              digitalWrite(D1, HIGH);
              delay(1000);
              digitalWrite(D3, HIGH);
              delay(1000);
              digitalWrite(D3, LOW);
              digitalWrite(D2, LOW);
              digitalWrite(D4, HIGH);
            }
          }
          
          // Vilkuv kollane
          if(payload == "2"){
            lampsOff();
            digitalWrite(D3, HIGH);
            delay(500);
            digitalWrite(D3, LOW);
          }
          
         
        }
      }
   }
  }
  Serial.println("------------------------------------");
}

void lampsOff(){
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);  
}
