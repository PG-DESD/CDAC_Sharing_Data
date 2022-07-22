/* ESP32 AWS IoT
 *  
 * Simplest possible example (that I could come up with) of using an ESP32 with AWS IoT.
 *  
 * Author: Anthony Elder 
 * License: Apache License v2
 * Sketch Modified by Tarun Bharani
 * Add in Char buffer utilizing sprintf to dispatch JSON data to AWS IoT Core
 * Use and replace your own SID, PW, AWS Account Endpoint, Client cert, private cert, x.509 CA root Cert
 */
#include <WiFiClientSecure.h>
#include <PubSubClient.h> // install with Library Manager, I used v2.6.0
/*
//Used the Below Liberary
//https://github.com/knolleary/pubsubclient

//Enter Your Wifi Name or HotSpot Name i.e. SSID
const char* ssid = "<YOUR-SSID>";
const char* password = "<YOUR-PASSWORD>";

const char* awsEndpoint = "<YOUR-ACCOUNT>-ats.iot.<YOUR-REGION>.amazonaws.com";
*/
const char* ssid = "Airtel";
const char* password = "Ridrun20";
//1. Sever Address
const char* awsEndpoint = "a1pkt6llab8sur-ats.iot.us-east-2.amazonaws.com";

// Update the certificate & Private Key strings below. Paste in the text of your AWS 
// device certificate and private key. 

// Device Certificate
static const char certificatePemCrt[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIULcsR3DKFexdrdHIfvmepZ8mOGtIwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIwMTAxMDA2NTc1
MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJm/mUBbKTCJsBHEPwUS
jhECHbMXCDTgSPtamXGz+LFXPz/c3w1OFtK8qNDgdrjr3zr293qZafN4OtEQE+pD
aBwFvTxGEIkLNVbztFHGHQ7PXOwZuMNyTWu1Uv/73VuIXVLOknmMvNJtlGNIdlHA
qF2Ry04UR2znhSuXKrfqj6G6XIZbpjWWmg+g+U66bv41EaGqRh/DmkNOgnu6Jd0e
N0sgZe5mt5A2F1jLGsLevrMs80kAiP6/h/AI8ArhiIHgi4vjEtp/uCjv3/vyhajr
XtlGtS6zlKCSrBGu36C0bZFKwMZWMf1xcH1qi/galhkeaTcX8Lgeyuppf/wff3Xh
LAsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUKlXsAC41wwXScXFiF/zYW5/F+i8wHQYD
VR0OBBYEFKh46pKMcvXAkWYMPD7+6oqDUJhgMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCbd2bJn6JOoKvdihuAiKvHBdrd
1Mz6QlK1lICA8vrov2wQzFruGMXvimEPTelh9GmsXAF7NN/L5lseo0zJZs5YytLs
cQYJPcNCosYh1Cv76lwIPOi6zwyGA3HaLubL765mb5yPHWvemy8SmhOv2cismktw
EsFfOrYyOKoZ6wY9rwoGOSRdyfEra3Ut5yBdD1CvA+mqO5+C77bli9em2b2ny+oa
B3VA9e2uGOP7AVrbEvz34ja4wxeW4Kc6SODXf4hyGkWU3XlCjV2v/Ex40X7quZ35
wUmK5QQajVh06DhFsF1VJ0Hh4Zf6zviOQeTyq7KUKqlMx6wsJ3kZjSfB54q6
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char privatePemKey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAmb+ZQFspMImwEcQ/BRKOEQIdsxcINOBI+1qZcbP4sVc/P9zf
DU4W0ryo0OB2uOvfOvb3eplp83g60RAT6kNoHAW9PEYQiQs1VvO0UcYdDs9c7Bm4
w3JNa7VS//vdW4hdUs6SeYy80m2UY0h2UcCoXZHLThRHbOeFK5cqt+qPobpchlum
NZaaD6D5Trpu/jURoapGH8OaQ06Ce7ol3R43SyBl7ma3kDYXWMsawt6+syzzSQCI
/r+H8AjwCuGIgeCLi+MS2n+4KO/f+/KFqOte2Ua1LrOUoJKsEa7foLRtkUrAxlYx
/XFwfWqL+BqWGR5pNxfwuB7K6ml//B9/deEsCwIDAQABAoIBAHW+pBEDP4IqkCqr
DlBGK4KfCjuzMde8xGeqtMS9PYIi/Q9diXzZBuWREgAVRxbLnQO9Sz4a62dH9lNR
as8HnF2Jj6jvR46MhOb4cGoHvQ0whUtTT4puqRgJn2znaFjHECFwjgCEZb8JqJB4
WBS35Lj0BKzhHuoqTHRbqp17B1ClBlwHAA15EXqj/iGVJwdGvyOo/lcCHEtSR6eB
Y8Dxvpa+ySXL9a3nSWHaSsiZRg805PyHBRipKIph18zf4nwA/0wegPgScrv88OI+
MWmMR7j12rh5kQV8xx+gRALyFQRite5lxb9klLiZoVjmhBfnnWsfVrIk97gk+25E
Q7/tctECgYEAzMzKiFcahco7vnziKD5hF1UW2DRrjOYssNsv/f+lZYHdGKHOBweO
rsUUeJJw8YDxMolvrvESWdK+TpOVILXubHBdI+0DqYynscpNwBjsQuxv8ycZ0S3Q
JV0D04U9mz99rDtB+nyD2A9gbKOoHxMzRWe8CHz6qTiXksagCtvoBJUCgYEAwC+B
sSbwNyPwJXCpS+tOjbxJ+GQQJbJXEHfCj+fj1TN7OcVk0ahtBTDVocGU/chCE6Lj
3xBZEJgp19CFI0aJY5Ushi2vFvkn2SkcI105/oyp73GkGZJqUr0Tu/XPl8hPa3j5
KZKv0PBMHUwP+iXMgk97kADP685Wz1/LMxaQph8CgYEAoPwqCFpP4vNBW09Xh0Lh
lzGvr2wlTrBwWOUzKHoYTV5zqbUm+qeaJQ+OM+kJFw3Ai3U1cVLWlfzu0113UCsy
q9L3pBHfWxvRhhP8YhA1R7YLmhsWVDOq9nPTWiXWc37JDuXVy0ytZt1PcpaCxUqW
duxABnwXnYV6wEmZ7G9IRrECgYBtS9cu/10HjtmpATxWn7ip5JYQvB9uwNDA3cr5
ekBY5JFE1pyym1184TvtZSEtfvENJ8r99dchF9hcEwtUd231A0Yx/NMhdosR9k45
UnCD8k1GjlNr85eh/EO31mC8CkAYd9EDspdodPBkjPhdI5f91+QGjl+w1EUMZIc0
Q7X5swKBgHP4omclNYGkZrJ87nae4zy2KMK55a5p1IeLWU405t86Sq5XVkyepmQh
HtlKcuWH+cdQzVx3ovUl7YXnPwXxy9qZl58QzpjnN7ejPEyuLaFr6h3F9Vx9vTPh
VJeAXpn1kQ/9Umg3H6ftJMdqU6NClBYeFe1OmdB9IDhGX1EFp4j7
-----END RSA PRIVATE KEY-----
)KEY";


// This is the AWS IoT CA Certificate from: 
// https://docs.aws.amazon.com/iot/latest/developerguide/managing-device-certs.html#server-authentication
// This one in here is the 'RSA 2048 bit key: Amazon Root CA 1' which is valid 
// until January 16, 2038 so unless it gets revoked you can leave this as is:
// Amazon Root CA 1
static const char rootCA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";


WiFiClientSecure wiFiClient;
void msgReceived(char* topic, byte* payload, unsigned int len);
PubSubClient pubSubClient(awsEndpoint, 8883, msgReceived, wiFiClient); 

void setup() {
  Serial.begin(115200); delay(50); Serial.println();
  Serial.println("ESP32 AWS IoT Example");
  Serial.printf("SDK version: %s\n", ESP.getSdkVersion());

  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  WiFi.waitForConnectResult();
  Serial.print(", WiFi connected, IP address: "); Serial.println(WiFi.localIP());

  wiFiClient.setCACert(rootCA);
  wiFiClient.setCertificate(certificatePemCrt);
  wiFiClient.setPrivateKey(privatePemKey);
}

unsigned long lastPublish;
int msgCount;

void loop() {

  pubSubCheckConnect();

   //If you need to increase buffer size, you need to change MQTT_MAX_PACKET_SIZE in PubSubClient.h
   char fakeData[128];

  float var1 =  random(55,77); //fake number range, adjust as you like
  float var2 =  random(77,99);
  sprintf(fakeData,  "{\"uptime\":%lu,\"temperature\":%f,\"humidity\":%f}", millis() / 1000, var1, var2);


  if (millis() - lastPublish > 10000) {
  //String msg = String("Hello from ESP32: ") + ++msgCount;
  // boolean rc = pubSubClient.publish("outTopic", msg.c_str());
  boolean rc = pubSubClient.publish("outTopic", fakeData);
    Serial.print("Published, rc="); Serial.print( (rc ? "OK: " : "FAILED: ") );
    Serial.println(fakeData);
    lastPublish = millis();

    
  }
}

void msgReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on "); Serial.print(topic); Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void pubSubCheckConnect() {
  if ( ! pubSubClient.connected()) {
    Serial.print("PubSubClient connecting to: "); Serial.print(awsEndpoint);
    while ( ! pubSubClient.connected()) {
      Serial.print(".");
      pubSubClient.connect("ESPthingXXXX");
      delay(1000);
    }
    Serial.println(" connected");
    pubSubClient.subscribe("inTopic");
  }
  pubSubClient.loop();
}
