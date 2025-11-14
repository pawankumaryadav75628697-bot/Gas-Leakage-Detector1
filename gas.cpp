const int MQ5_DigitalPin = 32;   // MQ-5 D0 pin → ESP32 GPIO32
const int LED_Pin        = 25;   // LED indicator pin

// Optional: adjustable delay between readings
const unsigned long READ_INTERVAL = 500;  
unsigned long lastReadTime = 0;

void setup() {
  Serial.begin(115200);

  pinMode(MQ5_DigitalPin, INPUT);
  pinMode(LED_Pin, OUTPUT);

  digitalWrite(LED_Pin, LOW);

  Serial.println("=====================================");
  Serial.println("      MQ-5 LPG Gas Detector Ready    ");
  Serial.println("   System Initializing... Please wait ");
  Serial.println("=====================================");
  delay(2000);   // Sensor warm-up time for stable output
}

void loop() {
  unsigned long currentTime = millis();
  
  // Read only after interval for stable sampling
  if (currentTime - lastReadTime >= READ_INTERVAL) {
    lastReadTime = currentTime;

    int gasState = digitalRead(MQ5_DigitalPin);

    if (gasState == LOW) {  
      // MQ-5 digital output LOW means gas detected
      digitalWrite(LED_Pin, HIGH);
      Serial.println("⚠️  ALERT: Gas Leakage Detected!");
    } else {
      digitalWrite(LED_Pin, LOW);
      Serial.println("Environment Safe. No Gas Detected.");
    }
  }
}
