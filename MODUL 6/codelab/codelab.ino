#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6C89Wu9__"
#define BLYNK_TEMPLATE_NAME "Piranti Cerdas"
#define BLYNK_AUTH_TOKEN "I8eCpvrG-wKvE3tgKGhzn8bHq2xCeBve"

#include <Blynk.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "mupay";
char pass[] = "alviyesz";

#include "DHT.h"
#define DHTPIN 25
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int buzzerPin = 32; // Pin buzzer (contoh: GPIO 14)

void setup()
{
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
    Serial.println("DHT11 Output!");
    dht.begin();
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); // Matikan buzzer saat startup
}

void loop()
{
    Blynk.run();
    timer.run();
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity))
    {
        Serial.println("Failed to read DHT11");
    }
    else
    {
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.print(" %\t");
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" *C");

        // Kirim data ke Blynk (Menukar V0 dan V1)
        Blynk.virtualWrite(V1, temperature);  // Kirim kelembaban ke pin virtual V1
        Blynk.virtualWrite(V0, humidity);  // Kirim suhu ke pin virtual V0

        // Kontrol buzzer berdasarkan suhu
        if (temperature > 30.0)
        {
           
          digitalWrite(buzzerPin, HIGH);
          delay(1000); // Keep the buzzer on for 1 second (1000 ms)
          digitalWrite(buzzerPin, LOW);
          Serial.println("PERINGATAN: Suhu sangat panas! Aktifkan kipas angin kandang segera.");
          Blynk.logEvent("peringatan_suhu_panas", String("PERINGATAN: Suhu sangat panas! Aktifkan kipas angin kandang segera! Temperature: ") + temperature);
        }
        else if (temperature > 25.0)
        {
            // Suhu hangat, nyalakan buzzer dengan suara sedang
             digitalWrite(buzzerPin, HIGH);
             delay(500); // Keep the buzzer on for 0.5 seconds (500 ms)
             digitalWrite(buzzerPin, LOW);
             Serial.println("PERINGATAN: Suhu hangat! Pertimbangkan untuk mengaktifkan kipas angin kandang.");
             Blynk.logEvent("peringatan_suhu_hangat", String("PERINGATAN: Suhu hangat! Pertimbangkan untuk mengaktifkan kipas angin kandang! Temperature: ") + temperature);
        }
        else
        {
            // Suhu normal, matikan buzzer
            digitalWrite(buzzerPin, LOW);
        }

        delay(1500);
    }
}