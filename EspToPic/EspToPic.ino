#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "string.h"

// Update these with values suitable for your network.
const char* ssid = "SEICAPG4";

const char* password = "seicpass4";
const char* mqtt_server = "10.0.1.1";
String str;


#define mqtt_port 1883
#define MQTT_SERIAL_SUBSCRIBE_TOPIC "/nodeMCUm/"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {delay(500);}
  randomSeed(micros());
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "NodeMCUClient-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {client.subscribe(MQTT_SERIAL_SUBSCRIBE_TOPIC);} 
    else {
      Serial.print("F\n");
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
  if (String(topic) == MQTT_SERIAL_SUBSCRIBE_TOPIC) {
    for (int i = 0; i < length; i++) {Serial.print((char)payload[i]);}
    Serial.print("\n");
  }
}

void setup() {
  Serial.begin(19200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}
void publishSerialData(char *MQTT_SERIAL_PUBLISH_CH, String serialData) {
  char buf[50];
  serialData.toCharArray(buf, 50);
  if (!client.connected()) {reconnect();}
  client.publish(MQTT_SERIAL_PUBLISH_CH, &buf[serialData.indexOf("_") + 1]);
}
void loop() {
  client.loop();
  Serial.flush();
  if (Serial.available() > 0) {
    str = Serial.readString();

    if (str.indexOf("Hey") >= 0) {Serial.print("A\n");}
    else if (str.indexOf("FirstMQ") >= 0) {
      publishSerialData("/nodeMCU/", str);
      Serial.print("B\n");
    }
    else if (str.indexOf("SecondMQ") >= 0) {
      publishSerialData("/nodeMCU2/", str);
      Serial.print("C\n");
    }
    else if (str.indexOf("ThirdMQ") >= 0) {
      publishSerialData("/nodeMCUT/", str);
      Serial.print("D\n");
    }
    else if (str.indexOf("FourthdMQ") >= 0) {
      publishSerialData("/nodeMCUH/", str);
      Serial.print("A\n");
    }
    else {Serial.print("Ups" + str);}
  }
}
