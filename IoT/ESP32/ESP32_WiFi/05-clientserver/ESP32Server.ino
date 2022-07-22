//////////////////////////////////////////////////////////////////////////////////
// Please use Your Mobile HotSpot to Test This Program                          //
// Also Note that CDAC Network has Jammers that Block the HOTSPOT of your Mobile//
//Client and Server Must be Connected to same HotSpot//
////////////////////////////////////////////////
#include <WiFi.h>

String  ClientRequest;
//Below IP Address Will be Used by Client to Connect to this Server
IPAddress staticIP316_10(192,168,1,21);
//Below is the IP Address of the Mobile Gateway
IPAddress gateway316_10(192,168,1,1);
IPAddress subnet316_10(255,255,255,0);

WiFiServer server(80);

WiFiClient client;

String myresultat;

String ReadIncomingRequest(){
while(client.available()) {
ClientRequest = (client.readStringUntil('\r'));
 if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0)){
myresultat = ClientRequest;
}
}
return myresultat;
}

void setup()
{
ClientRequest = "";

Serial.begin(115200);

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Benga_Boyzzzz","Benga@4321");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  WiFi.config(staticIP316_10, gateway316_10, subnet316_10);
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest = (ReadIncomingRequest());
    client.flush();
    Serial.println("HTTP Request From");
    Serial.println((client.remoteIP()));
    Serial.println("Original request");
    Serial.println(ClientRequest);
    ClientRequest.remove(0, 5);
    ClientRequest.remove(ClientRequest.length()-9,9);
    Serial.println("Request after Clear");
    Serial.println(ClientRequest);

}