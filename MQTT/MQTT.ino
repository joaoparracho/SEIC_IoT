#include "Arduino.h"
#include "string.h"
#include "stdint.h"
#include <ELClient.h>
#include <ELClientCmd.h>
#include <ELClientMqtt.h>

#define SEC 1000
#define BUFLEN 500
#define RED 5
#define GREEN 3
#define BLUE 4
#define LED1 8
// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient esp(&Serial1, &Serial1);
// Initialize CMD client (for GetTime)
ELClientCmd cmd(&esp);
// Initialize the MQTT client
ELClientMqtt mqtt(&esp);

const int analogInPin = A0;
const int digitalInPin = 2;
bool connected = false;
static uint32_t last=0;
static bool firstTime = true;
bool ledState = false;

void wifiCb(void* response) {
  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc()) {
    uint8_t status;res->popArg(&status, 1);
    if(status == STATION_GOT_IP) Serial.println("WIFI CONNECTED");
    else {Serial.print("WIFI NOT READY: "); Serial.println(status);}}
}

void publishData(){
  Serial.println("publishing to esp-link-g4/voltage");
  mqtt.publish("esp-link-g4/voltage","cona");
}

// Callback when MQTT is connected
void mqttConnected(void* response) {
  Serial.println("MQTT connected!");
  mqtt.subscribe("esp-link-g4/current");
  mqtt.subscribe("esp-link-g4/rgb");
  mqtt.subscribe("esp-link-g4/pot/0");
  mqtt.publish("esp-link-g4/pot/0",&String((double)analogRead(A2)*0.0048875)[0]);
  connected = true;
}

// Callback when MQTT is disconnected
void mqttDisconnected(void* response) {Serial.println("MQTT disconnected");connected = false;}

// Callback when an MQTT message arrives for one of our subscriptions
void mqttData(void* response) {
  ELClientResponse *res = (ELClientResponse *)response;

  Serial.print("Received: topic=");
  String topic = res->popString();
  Serial.println(topic);
  String data1 = res->popString();
  if (topic == "esp-link-g4/voltage"){

  }else if(topic == "esp-link-g4/current"){
	  ledState=!ledState;
	  digitalWrite(LED1,ledState);
  }else if(topic ==" esp-link-g4/rgb"){
	 analogWrite(RED,   255 - strtol(&data1.substring(0,2)[0],NULL,16));
	 analogWrite(GREEN, 255 - strtol(&data1.substring(2,4)[0],NULL,16));
	 analogWrite(BLUE,  255 - strtol(&data1.substring(4,6)[0],NULL,16));
  }else if (topic == "esp-link-g4/pot/0") mqtt.publish("esp-link-g4/pot/0",&String((double)analogRead(A2)*0.0048875)[0]);

  Serial.print("Data: ");
  Serial.println(data1);
}

void mqttPublished(void* response) {
  Serial.println("MQTT published");
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  last = millis();

  pinMode(analogInPin, INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);

  Serial.println("EL-Client starting!");
  bool ok;
  do {
    ok = esp.Sync();      // sync up with esp-link, blocks for up to 2 seconds
    if (!ok) Serial.println("EL-Client sync failed!");
  } while(!ok);
  Serial.println("EL-Client synced!");

  // Set-up callbacks for events and initialize with es-link.
  mqtt.connectedCb.attach(mqttConnected);
  mqtt.disconnectedCb.attach(mqttDisconnected);
  mqtt.publishedCb.attach(mqttPublished);
  mqtt.dataCb.attach(mqttData);
  mqtt.setup();

  Serial.println("EL-MQTT ready");
}

void loop() {
  esp.Process();
  if (connected && ( firstTime || (millis()-last) > 20*SEC) ) {
    publishData();
    firstTime = false;
    last = millis();
 }
}