#define BLYNK_TEMPLATE_ID "TMPL6C89Wu9__"
#define BLYNK_TEMPLATE_NAME "Piranti Cerdas"
#define BLYNK_AUTH_TOKEN "I8eCpvrG-wKvE3tgKGhzn8bHq2xCeBve"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <wificlient.h>
#include <BlynkSimpleEsp32.h>
#define LIGHT_SENSOR_PIN 32
BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "mupay";
char pass[] = "alviyesz";


void send_data(){
  delay(1000);
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.print(analogValue);

  Blynk.virtualWrite(V0, analogValue);
}
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, send_data);
}

void loop() {
  Blynk.run();
  timer.run();

}
