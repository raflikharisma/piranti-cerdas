#include <Wire.h>
#include <MPU6050_tockn.h>
#include <HTTPClient.h>
#include <WiFi.h>

MPU6050 mpu6050(Wire);

const int LDRPin = 32;
const int LEDpin = 27;
const char* ssid = "mupay";
const char* password = "alviyesz";
const char* serverName = "http://172.20.10.3/praktikum_modul4/input.php/";
const char* apiKey = "afbakjfwkabfkjabfakjfawjaf";



void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi....");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Local IP: " + WiFi.localIP().toString());
}

void analyzeLightSensor(int lightSensorValue) {
  Serial.print("Light Sensor Value: ");
  Serial.println(lightSensorValue);

  if (lightSensorValue >= 0 && lightSensorValue <= 50) {
    Serial.println("Keadaan Gelap");
    digitalWrite(LEDpin, HIGH);  // Nyalakan LED
  } else if (lightSensorValue > 50 && lightSensorValue <= 500) {
    Serial.println("Keadaan Redup");
    digitalWrite(LEDpin, HIGH);  // Nyalakan LED
  } else if (lightSensorValue > 500 && lightSensorValue <= 2000) {
    Serial.println("Cahaya Terang");
    digitalWrite(LEDpin, LOW);  // Matikan LED
  } else {
    Serial.println("Sangat Terang");
    digitalWrite(LEDpin, LOW);  // Matikan LED
  }
}

void analyzeMPUSensor() {
  mpu6050.update();
  Serial.print("Angle X: ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tAngle Y: ");
  Serial.println(mpu6050.getAngleY());

  if (mpu6050.getAngleX() > 10) {
    Serial.println("Sensor Miring Kiri");
  } else if (mpu6050.getAngleX() < -10) {
    Serial.println("Sensor Miring Kanan");
  } else if (mpu6050.getAngleY() > 10) {
    Serial.println("Sensor Miring Depan");
  } else if (mpu6050.getAngleY() < -10) {
    Serial.println("Sensor Miring Belakang");
  }
}
void sendDataToServer(int lightSensorValue) {
  char url[256];
  sprintf(url, "%s?apikey=%s&angkax=%f&angkay=%f&sensor=%d",
          serverName, apiKey, mpu6050.getAngleX(), mpu6050.getAngleY(), lightSensorValue);

  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
// 
void setup() {
  Serial.begin(9600);
  pinMode(LDRPin, INPUT);

  connectToWiFi();
  pinMode(LEDpin, OUTPUT);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
}

void loop() {
  int lightValue = analogRead(LDRPin);
  analyzeLightSensor(lightValue);
  analyzeMPUSensor();
  sendDataToServer(lightValue);
  delay(5000);
}