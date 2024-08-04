
#define BLYNK_TEMPLATE_ID           "TMPL6g-JU3KmH"
#define BLYNK_TEMPLATE_NAME         "Smart light"
#define BLYNK_AUTH_TOKEN            "qDVXEggEgwrXaAfZKtG908SWlWJDw_oP"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
const int lightSensorPin = A0;
const int relayPin = 2;
const int manualButtonPin = D4;

char ssid[] = "Phong 704";
char pass[] = "xuanphuong@123";

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
   pinMode(lightSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(manualButtonPin, OUTPUT);

  digitalWrite(relayPin, LOW);

  timer.setInterval(1000L, checkLightSensor);
  Serial.begin(115200);       
}
bool isManualMode = false;
bool manualLightState = false;
void loop() {
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V1) {
  isManualMode = param.asInt();
  if (isManualMode) {
    digitalWrite(relayPin, manualLightState ? HIGH : LOW);
  } else {
    
    checkLightSensor();
  }
}

BLYNK_WRITE(V2) {
  manualLightState = param.asInt();
  if (isManualMode) {
    digitalWrite(relayPin, manualLightState ? HIGH : LOW);
  }
}

void checkLightSensor() {
  if (!isManualMode) {
    int sensorValue = analogRead(lightSensorPin);
    Blynk.virtualWrite(V2, sensorValue);
    if (sensorValue > 500) {
      digitalWrite(relayPin, HIGH);
    } else {
      digitalWrite(relayPin, LOW);
    }
  }
}
