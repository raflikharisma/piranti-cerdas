#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6E-zw1inr"
#define BLYNK_TEMPLATE_NAME "Praktikum"
#define BLYNK_AUTH_TOKEN "gJi-an1gA4y43czFQxh1EId5PsIpTcR8"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LIGHT_SENSOR_PIN 33
#define RELAY_PIN 14

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "mupay";
char pass[] = "alviyesz";

int relayState;
WidgetLED led1(V1);



BLYNK_WRITE(V1){
  int relayValue = param.asInt();
  if (relayValue == 0) {
    digitalWrite(RELAY_PIN, HIGH);
    relayState = 1;
    Serial.println("Relay Turned Off");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    relayState = 0;
    Serial.println("Relay Turned On");
  }
}

void handleLDRRelay(int ldrval){
  if(ldrval <= 500 && relayState == 0){
    digitalWrite(RELAY_PIN, LOW);
  } else {
    digitalWrite(RELAY_PIN, HIGH);
  }
}

void sendLDRData(){
  delay(1000);
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog value: ");
  Serial.println(analogValue);
  handleLDRRelay(analogValue);
  Blynk.virtualWrite(V0, analogValue);
}

void setup(){
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, sendLDRData);
}

void loop() {
  Blynk.run();
  timer.run();
}