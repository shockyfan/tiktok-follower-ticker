#include <SPI.h>
#include "LedMatrix.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
WiFiClient wifiClient;

#define NUMBER_OF_DEVICES 4
#define CS_PIN 2
LedMatrix ledMatrix = LedMatrix(NUMBER_OF_DEVICES, CS_PIN);

const char* ssid = "<YOUR_SSID>";
const char* password = "<YOUR_PASSWORD>";

const char* serverName = "http://<YOUR_SERVER>:42100/api/followers";

unsigned long lastTime = 0;
unsigned long timerDelay = 30000; // every 30s (1000 * 30)
String followerCount;

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  ledMatrix.init();
  ledMatrix.setIntensity(10);
  ledMatrix.setText("Connecting");

  ledMatrix.clear();
  ledMatrix.setTextAlignment(0);
  ledMatrix.drawText();
  ledMatrix.commit();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");

  ledMatrix.setText("Connected");
  ledMatrix.clear();
  ledMatrix.setTextAlignment(0);
  ledMatrix.drawText();
  ledMatrix.commit();

  Serial.println(WiFi.localIP());
  updateFollowerCount();
}

void updateMatrix() {
  ledMatrix.clear();
  ledMatrix.setText(followerCount);
  ledMatrix.setTextAlignment(0);
  ledMatrix.drawText();
  ledMatrix.commit();
}

void updateFollowerCount() {
  if (WiFi.status() == WL_CONNECTED) {
    followerCount = httpGETRequest(serverName);
    Serial.println(followerCount);

    updateMatrix();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  lastTime = millis();

}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    updateFollowerCount();
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
  http.begin(wifiClient, serverName);
  int httpResponseCode = http.GET();

  String payload = "";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return payload;
}
