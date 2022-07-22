//This example demonstrates the ESP RainMaker with a custom device
//Video Link https://www.youtube.com/watch?v=eYVtHuLk008
//Arduino Project: IOT Devices With ESP32 (ESP Rainmaker)
//Documentation Link: https://github.com/espressif/arduino-esp32/tree/master/libraries/RainMaker#documentation

#include "RMaker.h"
#include "WiFi.h"
#include "WiFiProv.h"

#define DEFAULT_POWER_MODE true
#define DEFAULT_DIMMER_LEVEL 50
//Default Values of Objects
#define DEFAULT_TEMP_VALUE 24
#define DEFAULT_HUMI_VALUE 65
#define DEFAULT_PRESUR_VALUE 35
#define DEFAULT_GPIOX_STATE true

const char *service_name = "PROV_1234";
const char *pop = "abcd1234";

//Init Control Variable
static float tempVal = DEFAULT_TEMP_VALUE;
static float humiVal = DEFAULT_HUMI_VALUE;
static bool gpioxState = DEFAULT_GPIOX_STATE;

//GPIO Pins for virtual device
static int gpio_0 = 0; //for boot button switch
static int gpio_dimmer = 2; // for ESP32 onboard Blue LED 
static int gpiox = 2; // define gpiox as any pin no for testing purpose defined as 2

bool dimmer_state = true;

// The framework provides some standard device types like switch, lightbulb, fan, temperature sensor.
// But, you can also define custom devices using the 'Device' base class object, as shown here
//static Device my_device("Dimmer", "custom.device.dimmer", &gpio_dimmer);

//Creating my Custom Dashboad
static Device dashboard("Dashboard", "custom.device.dashboard");

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32S2
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on SoftAP\n", service_name, pop);
        printQR(service_name, pop, "softap");
#else
        Serial.printf("\nProvisioning Started with name \"%s\" and PoP \"%s\" on BLE\n", service_name, pop);
        printQR(service_name, pop, "ble");
#endif        
        break;
        default:;
    }
}

void write_callback(Device *device, Param *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device->getDeviceName();
    const char *param_name = param->getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        dimmer_state = val.val.b;
        (dimmer_state == false) ? digitalWrite(gpio_dimmer, LOW) : digitalWrite(gpio_dimmer, HIGH);
        param->updateAndReport(val);
    } 
    else if (strcmp(param_name, "Pressure (B)") == 0) {
        Serial.printf("\nReceived value = %2.2f for %s - %s\n", val.val.f, device_name, param_name);
        param->updateAndReport(val);
    }
    else if (strcmp(param_name, "GPIO State") == 0) {
        Serial.printf("Received value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        dimmer_state = val.val.b;
        (dimmer_state == false) ? digitalWrite(gpiox, LOW) : digitalWrite(gpiox, HIGH);
        param->updateAndReport(val);
    }
    
}

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
    pinMode(gpio_dimmer, OUTPUT);
    //setting GPIOX Direction
    pinMode(gpiox, OUTPUT);
    //setting default value for GPIOX
    digitalWrite(gpiox, DEFAULT_GPIOX_STATE);
    digitalWrite(gpio_dimmer, DEFAULT_POWER_MODE);

    Node my_node;    
    my_node = RMaker.initNode("ESP RainMaker Node");

    //Create custom dimmer device
    dashboard.addNameParam();
    dashboard.addPowerParam(DEFAULT_POWER_MODE);
    dashboard.assignPrimaryParam(dashboard.getParamByName(ESP_RMAKER_DEF_POWER_NAME));

    Param temperatureParam("Temperature (C)", NULL, value((float)DEFAULT_TEMP_VALUE), PROP_FLAG_READ );
    dashboard.addParam(temperatureParam);

    Param humidityParam("Humidity (%)", NULL, value((float)DEFAULT_HUMI_VALUE), PROP_FLAG_READ );
    dashboard.addParam(humidityParam);

    Param pressureParam("Pressure (B)", NULL, value((float)DEFAULT_PRESUR_VALUE), PROP_FLAG_WRITE );
    dashboard.addParam(pressureParam);

    Param gpioxState("GPIO State", NULL, value((bool)DEFAULT_GPIOX_STATE), PROP_FLAG_READ | PROP_FLAG_WRITE);
    gpioxState.addUIType(ESP_RMAKER_UI_TOGGLE);
    dashboard.addParam(gpioxState);
    
//    //Create and add a custom level parameter
//    Param level_param("Level", "custom.param.level", value(DEFAULT_DIMMER_LEVEL), PROP_FLAG_READ | PROP_FLAG_WRITE);
//    level_param.addBounds(value(0), value(100), value(1));
//    level_param.addUIType(ESP_RMAKER_UI_SLIDER);
//    dashboard.addParam(level_param);

    dashboard.addCb(write_callback);
    
    //Add custom dimmer device to the node   
    my_node.addDevice(dashboard);

    //This is optional 
    RMaker.enableOTA(OTA_USING_PARAMS);
    //If you want to enable scheduling, set time zone for your region using setTimeZone(). 
    //The list of available values are provided here https://rainmaker.espressif.com/docs/time-service.html
    // RMaker.setTimeZone("Asia/Shanghai");
    // Alternatively, enable the Timezone service and let the phone apps set the appropriate timezone
    RMaker.enableTZService();

    RMaker.enableSchedule();

    RMaker.start();

    WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32S2
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#else
    WiFiProv.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#endif
}

void loop()
{
    if(digitalRead(gpio_0) == LOW) { //Push button pressed

        // Key debounce handling
        delay(100);
        float randomtemp =  random(55,77); //fake number range, adjust as you like
        float randomhumi =  random(77,99);
        int startTime = millis();
        while(digitalRead(gpio_0) == LOW) delay(50);
        int endTime = millis();

        if ((endTime - startTime) > 10000) {
          // If key pressed for more than 10secs, reset all
          Serial.printf("Reset to factory.\n");
          RMakerFactoryReset(2);
        } else if ((endTime - startTime) > 3000) {
          Serial.printf("Reset Wi-Fi.\n");
          // If key pressed for more than 3secs, but less than 10, reset Wi-Fi
          RMakerWiFiReset(2);
        } else {
          // Toggle device state
          dimmer_state = !dimmer_state;
          Serial.printf("Toggle State to %s.\n", dimmer_state ? "true" : "false");
          dashboard.updateAndReportParam(ESP_RMAKER_DEF_POWER_NAME, dimmer_state);
          (dimmer_state == false) ? digitalWrite(gpio_dimmer, LOW) : digitalWrite(gpio_dimmer, HIGH);
          dashboard.updateAndReportParam("Temperature (C)",randomtemp);
          dashboard.updateAndReportParam("Humidity (%)",randomhumi);
      }
    }
    delay(100);
}
