/**
   BasicHTTPSClient.ino

    Created on: 20.08.2018

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
// Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
//36 AB B5 84 1E F1 AA C2 8E 4B 50 24 B2 A3 70 55 FB 96 F2 43
//E9 C5 89 A7 2A 5B 64 C5 B1 66 CF 1F 54 D2 83 60 CF C4 E7 08
//0x36, 0xAB, 0xB5, 0x84, 0x1E, 0xF1, 0xAA, 0xC2, 0x8E, 0x4B, 0x50, 0x24, 0xB2, 0xA3, 0x70, 0x55, 0xFB, 0x96, 0xF2, 0x43
const uint8_t fingerprint[20] = {0xE9, 0xC5, 0x89, 0xA7, 0x2A, 0x5B, 0x64, 0xC5, 0xB1, 0x66, 0xCF, 0x1F, 0x54, 0xD2, 0x83, 0x60, 0xCF, 0xC4, 0xE7, 0x08};
//const uint8_t fingerprint[20] = {0x36, 0xAB, 0xB5, 0x84, 0x1E, 0xF1, 0xAA, 0xC2, 0x8E, 0x4B, 0x50, 0x24, 0xB2, 0xA3, 0x70, 0x55, 0xFB, 0x96, 0xF2, 0x43};

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

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
  // Nupud
  pinMode(D1, INPUT);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    // client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://asjadeinternetcv-default-rtdb.europe-west1.firebasedatabase.app/1013.json")) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}
