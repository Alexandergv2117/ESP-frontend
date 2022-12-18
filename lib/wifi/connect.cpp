#include <ESP8266WiFi.h>

#include "config.h"

const char* AP_ssid = "AP-ESP8266";
const char* AP_password = "";

int ledIndicator;

void blink(int time) {
  digitalWrite(ledIndicator, HIGH);
  delay(time);
  digitalWrite(ledIndicator, LOW);
  delay(time);
}

void accessPoint() {
  WiFi.mode(WIFI_AP);

  Serial.print("Connecting to:\t");
  Serial.println(AP_ssid);

  while (!WiFi.softAP(AP_ssid, AP_password)) {
    blink(500);
    Serial.println(".");
  }

  Serial.print("IP: " + WiFi.softAPIP().toString() + "\n");
}

void connectWifi (int ledPin) {
  ledIndicator = ledPin;

  pinMode(ledIndicator, OUTPUT);
  digitalWrite(ledIndicator, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  for (int i = 0; i < 5; i++) {
    blink(500);

    if (WiFi.status() != WL_CONNECTED) Serial.println("Connecting to WiFi...");
    else i = 5;
  }

  if(WiFi.status() != WL_CONNECTED) accessPoint();
  else Serial.print("\nIP: " + WiFi.localIP().toString());
}
