#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

/* four data types being converted to char array */
char charArr[]="char array";
String str = "this is a string";
int integer = 7683;
float decimalNumber = 768.30000;

/* define the characteristic and it's propeties */
BLECharacteristic customCharacteristic(
  BLEUUID((uint16_t)0x1A00),
  BLECharacteristic::PROPERTY_READ |
  BLECharacteristic::PROPERTY_NOTIFY
);

/* define the UUID that our custom service will use */
#define serviceID BLEUUID((uint16_t)0x1700)

/* This function handles server callbacks */
bool deviceConnected = false;
class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* MyServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* MyServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("MyESP32"); // Name your BLE Device
  BLEServer *MyServer = BLEDevice::createServer();  //Create the BLE Server
  MyServer->setCallbacks(new ServerCallbacks());  // Set the function that handles server callbacks
  BLEService *customService = MyServer->createService(serviceID); // Create the BLE Service
  customService->addCharacteristic(&customCharacteristic);  // Create a BLE Characteristic
  customCharacteristic.addDescriptor(new BLE2902());  // Create a BLE Descriptor
  MyServer->getAdvertising()->addServiceUUID(serviceID);  // Configure Advertising
  customService->start(); // Start the service  
  MyServer->getAdvertising()->start();  // Start the server/advertising

  Serial.println("Waiting for a client to connect....");
}
void loop() {
  for (int i = 0; i < 4; ++i)
  {
    switch(i){
      case 0:{  //send char array
        customCharacteristic.setValue((char*)&charArr);
        customCharacteristic.notify();
        break;
      }
      case 1:{  //send string
        char buffer[str.length()+1];
        str.toCharArray(buffer,str.length()+1);
        customCharacteristic.setValue((char*)&buffer);
        customCharacteristic.notify();
        break;
      }
      case 2:{  //send integer
        char buffer[20];
        dtostrf(integer,1,0,buffer);
        customCharacteristic.setValue((char*)&buffer);
        customCharacteristic.notify();
        break;
      }
      case 3:{  //send float
        char buffer[20];
        dtostrf(decimalNumber,1,5,buffer);  //change 5 to whatever decimal precision you want
        customCharacteristic.setValue((char*)&buffer);
        customCharacteristic.notify();
        break;
      }
    }
    delay(1000);
  }
}