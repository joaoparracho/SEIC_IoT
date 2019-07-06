#include "Arduino.h"
#include "string.h"
#include "stdint.h"
#include <ELClient.h>
#include <ELClientCmd.h>
#include <ELClientMqtt.h>
#include <SPI.h>
#include "Wire.h"

#include "Adafruit_MPL3115A2.h"


#define SEC 1000
#define BUFLEN 500
#define RED 5
#define GREEN 3
#define BLUE 4
#define LED1 8
#define MOTOR 11
// Initialize a connection to esp-link using the normal hardware serial port both for
// SLIP and for debug messages.
ELClient esp(&Serial1, &Serial1);
ELClientCmd cmd(&esp);
ELClientMqtt mqtt(&esp);

const int analogInPin = A0;
const int digitalInPin = 2;
const int trigPin = 9;
const int echoPin = 10;

bool connected = false;
double lastPot;
double lastDist;
double lastAlt;
double lasttempC;
double lastPasc;
long duration;
int distance;
static uint32_t last=0;
static bool firstTime = true;
bool ledState = false;

int CS=48;
char POWER_CTL = 0x2D;  //Power Control Register
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32; //X-Axis Data 0
char DATAX1 = 0x33; //X-Axis Data 1
char DATAY0 = 0x34; //Y-Axis Data 0
char DATAY1 = 0x35; //Y-Axis Data 1
char DATAZ0 = 0x36; //Z-Axis Data 0
char DATAZ1 = 0x37; //Z-Axis Data 1
unsigned char values[10];
int x,y,z;
int lastx,lasty,lastz;

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void wifiCb(void* response) {
  ELClientResponse *res = (ELClientResponse*)response;
  if (res->argc() == 1) {
    uint8_t status;
    res->popArg(&status, 1);

    if(status == STATION_GOT_IP) Serial.println("WIFI CONNECTED");
    else {
      Serial.print("WIFI NOT READY: ");
      Serial.println(status);
    }
  }
}

void publishData(){
  double pot;
  float pascals = baro.getPressure();
  float altm    = baro.getAltitude();
  float tempC   = baro.getTemperature();
  String s;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
 
  pot = (double)analogRead(A2)*0.0048875;
  if(pot != lastPot){
    mqtt.publish("esp-link-g4/pot/0",&String(pot)[0]);
    lastPot=pot;
  }
  if (pascals != lastPasc){
    mqtt.publish("esp-link-g4/baro/press",&String(pascals/100000)[0]);
    Serial.print(pascals/3377); Serial.println(" Bar");
    lastPasc=pascals;
  }
  if (altm != lastAlt){
    mqtt.publish("esp-link-g4/baro/alt",&String(altm)[0]);
    Serial.print(altm); Serial.println(" meters");
    lastAlt=altm;
  }
  if (tempC != lasttempC){
    mqtt.publish("esp-link-g4/baro/temp",&String(tempC)[0]);
    Serial.print(tempC); Serial.println("*C");
    lasttempC=tempC;
  }
  if (distance != lastDist){
    mqtt.publish("esp-link-g4/sonar",&String(distance)[0]);
    Serial.print("Distance: ");
    Serial.println(distance);
    lastDist=distance;
  }

  readRegister(DATAX0, 6, values);
  x = ((int)values[1]<<8)|(int)values[0];
  y = ((int)values[3]<<8)|(int)values[2];
  z = ((int)values[5]<<8)|(int)values[4];

  if(lastx!=x || lasty!= y || lastz != z){
    s = String(x,DEC) + "_" + String(y,DEC) + "_" + String(z,DEC);
    Serial.print("XYZ: " + s + '\n');
    mqtt.publish("esp-link-g4/acl",&s[0]);
  }
  
}

void mqttConnected(void* response) {
  Serial.println("MQTT connected!");
  mqtt.subscribe("esp-link-g4/rgb");
  mqtt.subscribe("esp-link-g4/motor");
  lastPot=(double)analogRead(A2)*0.0048875;
  mqtt.publish("esp-link-g4/pot/0",&String(lastPot)[0]);
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
  if(topic =="esp-link-g4/current"){
    ledState=!ledState;
    digitalWrite(LED1,ledState);
  }else if(topic =="esp-link-g4/rgb"){
   analogWrite(RED,   255 - strtol(&data1.substring(0,2)[0],NULL,16));
   analogWrite(GREEN, 255 - strtol(&data1.substring(2,4)[0],NULL,16));
   analogWrite(BLUE,  255 - strtol(&data1.substring(4,6)[0],NULL,16));
  }else if(topic =="esp-link-g4/motor"){
    analogWrite(MOTOR,data1.toInt());
  }

  Serial.print("Data: ");
  Serial.println(data1);
}

void mqttPublished(void* response) {
  Serial.println("MQTT published");
}

void writeRegister(char registerAddress, char value){
  digitalWrite(CS, LOW);
  SPI.transfer(registerAddress);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
void readRegister(char registerAddress, int numBytes, unsigned char * values){
  char address = 0x80 | registerAddress;
  if(numBytes > 1)address = address | 0x40;
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  for(int i=0; i<numBytes; i++){values[i] = SPI.transfer(0x00);}
  digitalWrite(CS, HIGH);
}

void setup() {
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  Serial.begin(115200);
  Serial1.begin(115200);
  last = millis();

  pinMode(analogInPin, INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(MOTOR,OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  writeRegister(DATA_FORMAT, 0x01);
  writeRegister(POWER_CTL, 0x08); 

  Serial.println("EL-Client starting!");

  esp.wifiCb.attach(wifiCb); // wifi status change callback, optional (delete if not desired)
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
  if (connected && ( firstTime || (millis()-last) > 500) ) {
    //Serial.println("EL-Client synced!");
    while (!baro.begin());
    publishData();
    firstTime = false;
    last = millis();
 }
}
