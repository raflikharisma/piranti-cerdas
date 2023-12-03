#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

const int LDRPin = 32;
const int LEDpin = 27;


void analyzeLightSensor(int lightSensorValue) {
  Serial.print("Light Sensor Value: ");
  Serial.println(lightSensorValue);

  if (lightSensorValue >= 0 && lightSensorValue <= 50) {
    Serial.println("Keadaan Gelap");
    digitalWrite(LEDpin, HIGH);
  } else if (lightSensorValue > 50 && lightSensorValue <= 500) {
    Serial.println("Keadaan Redup");
    digitalWrite(LEDpin, HIGH);
  } else if (lightSensorValue > 500 && lightSensorValue <= 2000) {
    Serial.println("Cahaya Terang");
    digitalWrite(LEDpin, LOW);
  } else {
    Serial.println("Sangat Terang");
    digitalWrite(LEDpin, LOW);
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

// 
void setup() {
  Serial.begin(9600);
  pinMode(LDRPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
}

void loop() {
  int lightValue = analogRead(LDRPin);
  analyzeLightSensor(lightValue);
  analyzeMPUSensor();
  delay(1000);
}
