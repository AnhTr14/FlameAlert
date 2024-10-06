#include <SoftwareSerial.h>

#define Rx 12
#define Tx 11
#define TEMPERATURE_SENSOR A1
#define FLAME_SENSOR 7
#define AIRQUALITY_SENSOR A2
#define BUZZER 6

float temperature;
int isflame, airquality, isbuzzer;

SoftwareSerial mySerial(Tx, Rx);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(BUZZER, OUTPUT); 
}

void loop() {
  delay(3000);
  
  digitalWrite(BUZZER, LOW);
  temperature = readTemp();
  airquality = readAirQuality();
  isflame = isFlame();
  isbuzzer = Check();
  sendData();


  Serial.print(temperature);
  Serial.print(",");
  Serial.print(isflame);
  Serial.print(",");
  Serial.print(airquality);
  Serial.println("");

}

void sendData() {
  String s = String(temperature) + "%" + String(isflame) + "%" + String(airquality) + "%" + String(isbuzzer) + "%";
  mySerial.println(s);
}

float readTemp() {
  float temp = analogRead(TEMPERATURE_SENSOR);
  temp = (5.0*temp*100.0 / 1024.0);
  return temp;
}

int isFlame() {
  int x = digitalRead(FLAME_SENSOR);
  return 1-x;
}

float readAirQuality() {
  int air = analogRead(AIRQUALITY_SENSOR);
  return air;
}

int Check() {
  if (isflame == 1 || airquality > 100 || temperature >= 50) {
    digitalWrite(BUZZER, HIGH);
    return 1;
  }
  return 0;
}
