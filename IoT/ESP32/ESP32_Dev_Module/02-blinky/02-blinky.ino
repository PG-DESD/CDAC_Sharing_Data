#define PIN_LED 2

// Runs once on bootup
void setup(){

  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println("Setup complete");
}

// Runs as infinite loop like "while(true)" after setup() completes
void loop(){

  Serial.println("LED ON");
  digitalWrite(PIN_LED, HIGH);
  delay(500);

  Serial.println("LED OFF");
  digitalWrite(PIN_LED, LOW);
  delay(500);
  
}
