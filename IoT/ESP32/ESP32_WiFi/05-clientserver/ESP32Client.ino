//////////////////////////////////////////////////////////////////////////////////
// Please use Your Mobile HotSpot to Test This Program                          //
// Also Note that CDAC Network has Jammers that Block the HOTSPOT of your Mobile//
////////////////////////////////////////////////
#include <WiFi.h>

WiFiClient client;

String myurl = "/";
void setup()
{
Serial.begin(115200);

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("Your_SSID_Name","Password");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected to HotSpot");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  Serial.println("Note the IP Address and Find the Network IP");
  Serial.println("Configure the same Network IP in Server");
}


void loop()
{

    if (client.connect("192.168.1.10", 80)) 
	{ 
	  Serial.println("OK :Connected To Server");
	  Serial.println("Sending Data to Server");
      myurl += "yes";
      client.print(String("GET ") + myurl + " HTTP/1.1\r\n" +
                "Host: " + "192.168.1.10" + "\r\n" +
               "Connection: close\r\n\r\n");
      myurl="/";

    }
	else 
	{
		Serial.println("NOK : Unable Connect Server");
	}
	
    delay(1000);
    
    

}