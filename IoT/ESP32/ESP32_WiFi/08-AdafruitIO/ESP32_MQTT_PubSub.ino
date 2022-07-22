
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "tarun3743"
#define AIO_KEY  "6c010021a8484108954c62bfc27c099e"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

int  i;
boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}

Adafruit_MQTT_Publish myfeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/myfeed");
Adafruit_MQTT_Subscribe switch1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/switch1");
void setup()
{
i = 0;
Serial.begin(9600);

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("TitaniumG02","Nvidia@1");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  mqtt.subscribe(&switch1);
}


void loop()
{

    i = (random(100,200));
    if (MQTT_connect()) {
      if (myfeed.publish(i)) {
        Serial.println("Random Data sent");
        Serial.println(i);

      } else {
        Serial.println("Problem to Send Random Number");

      }

    } else {
      Serial.println("Problem to Connect to site");

    }
    delay(2000);

    
    if (MQTT_connect()) {
      Serial.println("Subscribe Event");
      Adafruit_MQTT_Subscribe *customswitch;
      while ((customswitch = mqtt.readSubscription(5000))) {
        if (customswitch == &switch1) {
          Serial.println("Inside Button");
          Serial.println(((char *)switch1.lastread));

        }

      }

    }

}
