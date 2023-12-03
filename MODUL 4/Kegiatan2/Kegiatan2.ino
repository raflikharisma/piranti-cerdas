int LDR_Val = 0;
int SENSOR = 14;
int LED = 23;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

}

void loop() {
  LDR_Val = analogRead(SENSOR);
  Serial.print("LDR Output: ");
  Serial.println(LDR_Val);
  if(LDR_Val > 100){
    Serial.println("Cahaya Terang");
    digitalWrite(LED, LOW);
  }
  else{
    Serial.println("Cahaya Gelap");
    digitalWrite(LED, HIGH);
  }
  delay(1000);

}
