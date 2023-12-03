#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define SENSORPIN 34
#define LEDPIN 23

const char* ssid = "mupay";
const char* password = "alviyesz";
const char* serverName = "http://172.20.10.3/pirdas_modul4/cahaya.php";

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  delay(1000);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  String wifiName = WiFi.SSID();
  String localWifiIP = WiFi.localIP().toString();
  Serial.println();
  Serial.println("Connected to " +wifiName);
  Serial.println("Local IP WiFi: " +localWifiIP);
}

void loop() {
  int ldr_value = analogRead(SENSORPIN);
  if(ldr_value > 100){
    Serial.println("Cahaya Terang");
    digitalWrite(LEDPIN, LOW);
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }
  else{
    Serial.println("Cahaya Gelap");
    digitalWrite(LEDPIN, HIGH);
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }
  delay(3000);
String url = serverName;
url += "?ldr_value=";
url += String(ldr_value);

HTTPClient http;
http.begin(url);
int httpResponseCode = http.GET();
if(httpResponseCode == 200){
  Serial.println("Data sent succesfully!");
}
else{
  Serial.print("Error Code: ");
  Serial.println(httpResponseCode);
}
http.end();
delay(1000);
}
