***************************************************************************************

Link: https://www.arduino.cc/reference/en/libraries/wifi/


********************************************************************************************************************************************
WiFi - WiFi.begin()
Description
Initializes the WiFi library’s network settings and provides the current status.

Syntax
WiFi.begin();
WiFi.begin(ssid);
WiFi.begin(ssid, pass);
WiFi.begin(ssid, keyIndex, key);
Parameters
ssid: the SSID (Service Set Identifier) is the name of the WiFi network you want to connect to.

keyIndex: WEP encrypted networks can hold up to 4 different keys. This identifies which key you are going to use.

key: a hexadecimal string used as a security code for WEP encrypted networks.

pass: WPA encrypted networks use a password in the form of a string for security.

Returns
WL_CONNECTED when connected to a network WL_IDLE_STATUS when not connected to a network, but powered on

Example
#include <WiFi.h>

//SSID of your network
char ssid[] = "yourNetwork";
//password of your WPA Network
char pass[] = "secretPassword";

void setup()
{
 WiFi.begin(ssid, pass);
}

void loop () {}

******************************************************************************************************************************

WiFi - WiFi.status()
Description
Return the connection status.

Syntax
WiFi.status();
Parameters
none

Returns
WL_CONNECTED: assigned when connected to a WiFi network; WL_NO_SHIELD: assigned when no WiFi shield is present; WL_IDLE_STATUS: it is a temporary status assigned when WiFi.begin() is called and remains active until the number of attempts expires (resulting in WL_CONNECT_FAILED) or a connection is established (resulting in WL_CONNECTED); WL_NO_SSID_AVAIL: assigned when no SSID are available; WL_SCAN_COMPLETED: assigned when the scan networks is completed; WL_CONNECT_FAILED: assigned when the connection fails for all the attempts; WL_CONNECTION_LOST: assigned when the connection is lost; WL_DISCONNECTED: assigned when disconnected from a network;

Example

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WEP network, SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, keyIndex, key);

   
void loop() {
  // check the network status connection once every 10 seconds:
  delay(10000);
 Serial.println(WiFi.status());
}

 
***************************************************************************************************************************************
WiFi - WiFi.disconnect()
Description
Disconnects the WiFi shield from the current network.

Syntax
WiFi.disconnect();
Parameters
none

Returns
nothing

************************************************************************
WiFi - IPAddress.localIP()
Description
Gets the WiFi shield’s IP address

Syntax
IPAddress.localIP();
Parameters
none

Returns
the IP address of the shield

Example


 //print the local IP address
  ip = WiFi.localIP();
  Serial.println(ip);



***************************************************************************************************
WiFi - WiFiServer()
Description
Creates a server that listens for incoming connections on the specified port.

Syntax
Server(port);
Parameters
port: the port to listen on (int)

Returns
None

Example

WiFiServer server(80);


*******************************************************************************************************************
WiFi - server.begin()
Description
Tells the server to begin listening for incoming connections.

Syntax
server.begin()
Parameters
None

Returns
None

WiFiServer server(80);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
    Serial.print("Connected to wifi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);


************************************************************************************
WiFi - server.available()
Description
Gets a client that is connected to the server and has data available for reading. The connection persists when the returned client object goes out of scope; you can close it by calling client.stop().

available() inherits from the Stream utility class.

Syntax
server.available()
Parameters
None

Returns
a Client object; if no Client has data available for reading, this object will evaluate to false in an if-statement

Example
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Network";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
    Serial.print("Connected to wifi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

  }
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {

    if (client.connected()) {
      Serial.println("Connected to client");
    }

    // close the connection:
    client.stop();
  }
}
***********************************************************************************
WiFi - server.write()
Description
Write data to all the clients connected to a server.

Syntax
server.write(data)
Parameters
data: the value to write (byte or char)

Returns
byte : the number of bytes written. It is not necessary to read this.

Example
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "yourNetwork";
char pass[] = "yourPassword";
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  else {
    server.begin();
  }
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client == true) {
       // read bytes from the incoming client and write them back
    // to any clients connected to the server:
    server.write(client.read());
  }
}

***********************************************************************************
WiFi - server.println()
Description
Prints data, followed by a newline, to all the clients connected to a server. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters ‘1’, ‘2’, ‘3’).

Syntax
server.println()
server.println(data)
server.println(data, BASE)
Parameters
data (optional): the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers: DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

Returns
byte println() will return the number of bytes written, though reading that number is optional

***************************************************************************************
WiFi - WiFiClient()
Description
Creates a client that can connect to to a specified internet IP address and port as defined in client.connect().

Syntax
WiFiClient()
Parameters
none

Example
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {

}
**************************************************************************************
WiFi - client.connected()
Description
Whether or not the client is connected. Note that a client is considered connected if the connection has been closed but there is still unread data.

Syntax
client.connected()
Parameters
none

Returns
Returns true if the client is connected, false if not.

Example
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(74,125,115,105);  // Google

// Initialize the client library
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {
   if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}
****************************************************************************************************
WiFi - client.connect()
Description
Connect to the IP address and port specified in the constructor. The return value indicates success or failure. connect() also supports DNS lookups when using a domain name (ex:google.com).

Syntax
client.connect(ip, port)
client.connect(URL, port)
Parameters
ip: the IP address that the client will connect to (array of 4 bytes)

URL: the domain name the client will connect to (string, ex.:“arduino.cc”)

port: the port that the client will connect to (int)

Returns
Returns true if the connection succeeds, false if not.

Example
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
char servername[]="google.com";  // remote server we will connect to

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(servername, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {

}
*********************************************************************************************************
WiFi - client.write()
Description
Write data to the server the client is connected to.

Syntax
client.write(data)
Parameters
data: the byte or char to write

Returns
byte: the number of characters written. it is not necessary to read this value.
*******************************************************************************************************************
WiFi - client.println()
Description
Print data, followed by a carriage return and newline, to the server a client is connected to. Prints numbers as a sequence of digits, each an ASCII character (e.g. the number 123 is sent as the three characters ‘1’, ‘2’, ‘3’).

Syntax
client.println()
client.println(data)
client.print(data, BASE)
Parameters
data (optional): the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers: DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

Returns
byte: return the number of bytes written, though reading that number is optional
*************************************************************************************************************************************************************************************************************************************************
WiFi - client.available()
Description
Returns the number of bytes available for reading (that is, the amount of data that has been written to the client by the server it is connected to).

available() inherits from the Stream utility class.

Syntax
client.available()
Parameters
none

Returns
The number of bytes available.

Example
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "myNetwork";          //  your network SSID (name)
char pass[] = "myPassword";   // your network password

int status = WL_IDLE_STATUS;
char servername[]="google.com";  // Google

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  }
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(servername, 80)) {
      Serial.println("connected");
      // Make a HTTP request:
      client.println("GET /search?q=arduino HTTP/1.0");
      client.println();
    }
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}
*************************************************************************************************************************************************
WiFi - client.read()
Read the next byte received from the server the client is connected to (after the last call to read()).

read() inherits from the Stream utility class.

Syntax
client.read()
Parameters
none

Returns
The next byte (or character), or -1 if none is available.
********************************************************************************************************************
WiFi - client.flush()
Discard any bytes that have been written to the client but not yet read.

flush() inherits from the Stream utility class.

Syntax
client.flush()
Parameters
none

Returns
none
********************************************************************************************************************************
WiFi - client.stop()
Disconnect from the server

Syntax
client.stop()
Parameters
none

Returns
none
***************************************************************************************************************