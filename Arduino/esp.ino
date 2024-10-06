#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "FirebaseESP8266.h"
#include <SoftwareSerial.h>

#define Rx D2
#define Tx D1
SoftwareSerial mySerial(Tx, Rx);

#define WIFI_SSID "Thanh Tam" 
#define WIFI_PASSWORD "31072002" 
#define FIREBASE_HOST "baochay-7d403-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "L9HpRKb8UHUPGfaJ6QBp2wm0KuWwL3NFiVd385Yy"

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  connectWifi();
  connectFirebase();
}

void loop() {
  if (mySerial.available()) { 
    unsigned long startTime = millis();
    String s = mySerial.readString();
    sendDatatoFirebase(s);
    unsigned long endTime = millis();
    unsigned long responseTime = endTime - startTime;

    Serial.print("Response time: ");
    Serial.println(responseTime);
  }
}

void sendDatatoFirebase(String data) {
  String s = "";
  float temp = 0;
  int flame = 0, air = 0, check = 0;
  int x = 0;

  for (int i = x; i < data.length(); ++i) {
    ++x;
    if (data[i] != '%') s+=data[i];
    else {
      temp = s.toFloat();
      s = "";
      Serial.print(temp);
      Serial.print(",");
      break;
    }
  }

  for (int i = x; i < data.length(); ++i) {
    ++x;
    if (data[i] != '%') s+=data[i];
    else {
      flame = s.toInt();
      s = "";
      Serial.print(flame);
      Serial.print(",");
      break;
    }
  }

  for (int i = x; i < data.length(); ++i) {
    ++x;
    if (data[i] != '%') s+=data[i];
    else {
      air = s.toInt();
      s = "";
      Serial.print(air);
      Serial.print(",");
      break;
    }
  }

  for (int i = x; i < data.length(); ++i) {
    ++x;
    if (data[i] != '%') s+=data[i];
    else {
      check = s.toInt();
      s = "";
      Serial.print(check);
      Serial.println(" .");
      break;
    }
  }

  Firebase.setFloat(firebaseData, "Baochay/NhietDo", temp);
  Firebase.setInt(firebaseData, "Baochay/TiaLua", flame);
  Firebase.setInt(firebaseData, "Baochay/KhongKhi", air);
  Firebase.setInt(firebaseData, "Baochay/TinhTrangChay", check);
}

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("Connecting...");
  Serial.print("WiFi Connected. IP Address:");
  Serial.println(WiFi.localIP());
}

void connectFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

