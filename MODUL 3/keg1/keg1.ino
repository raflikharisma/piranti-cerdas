#include <WiFi.h>

const char* mainSSID = "mupay";
const char* mainPassword = "alviyesz";
const int maxConnectionAttempts = 10;
int connectionAttempts = 0;

void setup() {
  Serial.begin(9600);
  connectToMainNetwork();
}

void loop() {
  // Your main code can go here, and it will continuously check and reconnect as needed.
}

void connectToMainNetwork() {
  connectionAttempts = 0;  // Reset connection attempts counter
  WiFi.begin(mainSSID, mainPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to the main WiFi...");

    connectionAttempts++;

    if (connectionAttempts >= maxConnectionAttempts) {
      Serial.println("Failed to connect to the main WiFi after 10 attempts. Switching to an open network...");
      connectToOpenNetwork();
      return;
    }
  }

  Serial.println("Connected to the main WiFi");
  Serial.print("The WiFi SSID is: ");
  Serial.println(mainSSID);
}

void connectToOpenNetwork() {
  WiFi.disconnect();

  int numNetworks = WiFi.scanNetworks();

  for (int i = 0; i < numNetworks; i++) {
    if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
      Serial.println("Connecting to an open network: " + WiFi.SSID(i));
      WiFi.begin(WiFi.SSID(i).c_str());

      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to the open WiFi...");
      }

      Serial.println("Connected to an open WiFi");
      Serial.println("Connected to " +  WiFi.SSID(i));
      
      return; // Exit the loop after connecting to an open network
    }
  }

  Serial.println("No open network found. Reconnecting to the main network.");
  connectToMainNetwork(); // If no open network is found, reconnect to the main network
}
