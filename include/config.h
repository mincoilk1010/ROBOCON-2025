#pragma once
#include <WiFi.h>
#include <PubSubClient.h>
#include <NimBLEDevice.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-1234-1234-1234-1234567890ab"

extern NimBLEServer*       pServer;
extern NimBLEService*      pService;
extern NimBLECharacteristic* pChar;

//WiFi and MQTT config
const char* ssid = "thuchanhAT T5";
const char* password = "12345679";
const char* mqttServer = "172.19.237.126";
const int mqttPort = 1883;

extern WiFiClient espClient;
extern PubSubClient client;

// UART 
#define RXD1 44
#define TXD1 43