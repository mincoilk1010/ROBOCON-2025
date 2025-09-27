#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#include "servo_arm.h"
#include "robot.h"
#include "config.h"
#include "magnet.h"

// NimBLEServer*       pServer   = nullptr;
// NimBLEService*      pService  = nullptr;
// NimBLECharacteristic* pChar   = nullptr;


// class MyCallbacks : public BLECharacteristicCallbacks {
//   void onWrite(BLECharacteristic *pCharacteristic) {
//     std::string value = pCharacteristic->getValue();
//     if (value.length() > 0) {
//       Serial.print("Nhận từ Node-RED: ");
//       Serial.println(value.c_str());
//     }
//   }
// };

WiFiClient espClient;
PubSubClient client(espClient);

void mqttCallback(char* topic, byte* message, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg += (char)message[i];
  }
  Serial.print("MQTT ["); Serial.print(topic); Serial.print("]: "); Serial.println(msg);

  if (String(topic) == "robot/cmd") {
    if (msg.length() > 0) {
      handleCommandServo(msg[0]);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT Server ...");
    if (client.connect("ESP32Client")) {
      Serial.println("Connected!");
      client.subscribe("robot/cmd");
    } else {
      Serial.print("Error: ");
      Serial.print(client.state());
      Serial.println("Try to connect to MQTT after 5s.");
      delay(5000);
    }
  }
}

void setup(){

  Serial.begin(115200); 
  //Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);

//BLE setup
  // NimBLEDevice::init("Tên thiết bị");
  // NimBLEServer *pServer = NimBLEDevice::createServer();
  // auto pAdvertising = NimBLEDevice::getAdvertising();

  // pChar = pService->createCharacteristic(
  //            CHARACTERISTIC_UUID,
  //            BLECharacteristic::PROPERTY_WRITE
  //         );
  // pChar->setCallbacks(new MyCallbacks());

  // pService->start();
  // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  // pAdvertising->addServiceUUID(SERVICE_UUID);
  // pAdvertising->start();
  // Serial.println("Đang quảng bá BLE, chờ Node-RED kết nối...");

//WiFi setup
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 40) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  Serial.print("\nWiFi connected. IP: ");
  Serial.println(WiFi.localIP());
//   // MQTT setup
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);
  //Initializating robot
    initRobot();
    initServo();
    Serial.println("Robot is ready");
// 
}

void loop(){
    if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Lost connecting WiFi, try again...");
    WiFi.reconnect();
    delay(5000);
  }

  if(!client.connected()){
    reconnect();
  }
  client.loop();
  //Receive data from UART
//   if (Serial1.available()){
//     char cmd = Serial1.read();
//     handleCommandMotor(cmd);
//     handleCommandServo(cmd);
//   }
}