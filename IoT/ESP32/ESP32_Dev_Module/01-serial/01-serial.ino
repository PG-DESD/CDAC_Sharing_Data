// Runs once on bootup
void setup(){
  Serial.begin(115200);
  Serial.println("Setup started");
}

// Runs as infinite loop like "while(true)" after setup() completes
void loop(){

  //ESP32 specific log modes
  log_e("test - error");
  log_w("test - warning");
  log_i("test - info");
  log_d("test - debug");

  //No verbose option in Arduino IDE
  log_v("test - verbose");

  //Serial.println does not show up when set to info/debug"
  Serial.println("Testing serial output");
  Serial.println();

  //Pause here for 1000ms
  delay(1000);
}
