  #include <MPU6050_tockn.h>
  #include <WiFi.h>
  #include <Wire.h>
  MPU6050 mpu6050(Wire);

  const char* ssid = "mupay";
  const char* password = "alviyesz";

  const int buzzerPin = 25;
  const int led = 13;

  void setup() {
    Serial.begin(115200);
    pinMode(buzzerPin, OUTPUT);
    pinMode(led, OUTPUT);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets();
  }

  void loop() {
    mpu6050.update();
    Serial.print("Angle X : ");
    Serial.print(mpu6050.getAngleX());
    Serial.print("\tAngle Y : ");
    Serial.println(mpu6050.getAngleY());
    if (mpu6050.getAngleX() > 20) {
      analogWrite(buzzerPin, 63);
      analogWrite(led, 255);
      Serial.println("Tilted Forward");
    } else if (mpu6050.getAngleX() < -20) {
      analogWrite(buzzerPin, 126);
      analogWrite(led, 255);
      Serial.println("Tilted Back");
    } else if (mpu6050.getAngleY() > 20) {
      analogWrite(buzzerPin, 189);
      analogWrite(led, 255);
      Serial.println("Tilted Forward");
      Serial.println("Tilted To The Left");
    } else if (mpu6050.getAngleY() < -20) {
      analogWrite(buzzerPin, 255);  // Kedap-kedip LED 5 kali
      analogWrite(led, 255);  // Hidupkan LED // Tahan selama 0.5 detik
      Serial.println("Tilted To The Right");
    } else {
      analogWrite(buzzerPin, 0);
      analogWrite(led, 0);
    }
   delay(500);
}