#define LIGHT_SENSOR_PIN 27
#define ledPin 32 // ESP32 pin GIOP36 (ADC0)

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 500) {
    Serial.println("  Gelap");
    analogWrite(32, 255);
  } else if (analogValue > 500 && analogValue < 1000 ) {
    Serial.println("  Redup");
    analogWrite(32, 64);
    delay(200);
    analogWrite(32, 0);
    delay(200);
    
  } else if (analogValue > 1000) {
    Serial.println("  Terang");
    analogWrite(32, 0);
  }


  delay(500);
}
