#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <iostream>
#include <sstream>

//Bluetooth Variables//
#define SERVICE_UUID "7abed0ab-5d98-4395-986f-f4ad005f5ea9"
#define DROP_CONTROLLER_CHARACTERISTIC_UUID "7abed0ab-5d98-4395-986f-f4ad005f5ea9"
#define TIME_OFFSET_CHARACTERISTIC_UUID "f49e3c75-b9bf-46b0-8b34-727e7445fb0d"
#define NOTIFY_CHARACTERISTIC_UUID "9767edc0-2279-41e2-8bff-3fe95b685ab9"
#define DEVICE_NAME "Trident"
#define BUILTIN_LED 2

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *DropControllCharacteristic;
BLECharacteristic *TimeOffsetCharacteristic;
BLECharacteristic *NotifyCharacteristic;

bool deviceConnected = false;
bool oldDeviceConnected = false;

int cameraDelayVal = 0;
int dropDelayVal = 0;
uint8_t txValue = 0;
//******************//

int convertBTStringToInt(std::string rxValue) //Covert values from phone from string to int
{
  int dataVal = 0;
  
  std::stringstream valBuffer(rxValue);
  valBuffer >> dataVal;

  return dataVal;
}

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

class DropControllerCallback : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();
    //read data as byte pCharacteristic->getData() pCharacteristic instead of   pCharacteristic->getValue();
    if (rxValue.length() > 0)
    {
      Serial.println("*********");
      Serial.print("Characteristic Uuid ");
      std::string id = pCharacteristic->getUUID().toString();
      
      for (int i = 0; i < id.length(); i++)
        Serial.print(id[i]);

      Serial.print(" Received Value: ");
      for (int i = 0; i < rxValue.length(); i++)
        Serial.print(rxValue[i]);

      Serial.println();
      Serial.println("*********");
      if (rxValue == "0")
      {
        digitalWrite(BUILTIN_LED, LOW);
      }
      else
      {
        digitalWrite(BUILTIN_LED, HIGH);
      }
    }
    cameraDelayVal = convertBTStringToInt(rxValue);
  }
};

class TimeOffsetSetCallback : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string rxValue = pCharacteristic->getValue();
    uint8_t* rxByteValue = pCharacteristic->getData();
    int* dropperNumber=(int*)rxByteValue;
    int* numberOfDrops=dropperNumber+1;
    int* delay=numberOfDrops+1;
    int* size=delay+1;
    uint8_t* enabled=(uint8_t*)(size+1);

    if (rxValue.length() > 0)
    {
      Serial.println("*********");
      Serial.print("Characteristic Uuid ");
      std::string id = pCharacteristic->getUUID().toString();
      for (int i = 0; i < id.length(); i++)
        Serial.print(id[i]);

      Serial.print("Received Value: ");
      //for (int i = 0; i < rxValue.length(); i++)
     //   Serial.print(rxValue[i]);

      Serial.println("*********");
      Serial.print("Dropper Number:");
      Serial.println((*dropperNumber));
      Serial.print("Number of Drops:");
      Serial.println((*numberOfDrops));
      Serial.print("Delay:");
      Serial.println((*delay));
      Serial.print("Size:");
      Serial.println((*size));
      Serial.print("Enabled:");
      Serial.println((*enabled));
      //delay(30);
      NotifyCharacteristic->setValue(rxValue);
      NotifyCharacteristic->indicate();
      //delay(30);

    }
    dropDelayVal = convertBTStringToInt(rxValue);
  }
};

void bluetoothSetup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(BUILTIN_LED, OUTPUT);

  BLEDevice::init(DEVICE_NAME);
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);
  pServer->setCallbacks(new MyServerCallbacks());
  DropControllCharacteristic = pService->createCharacteristic(
      DROP_CONTROLLER_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  TimeOffsetCharacteristic = pService->createCharacteristic(
      TIME_OFFSET_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  NotifyCharacteristic = pService->createCharacteristic(
      NOTIFY_CHARACTERISTIC_UUID,
       BLECharacteristic::PROPERTY_READ|BLECharacteristic::PROPERTY_INDICATE);


  BLEDescriptor *TimeOffsetDescription = new BLEDescriptor((uint16_t)0x2901); // Characteristic User Description
  TimeOffsetDescription->setValue("Time Offset Value");
  BLEDescriptor *DropcontrollerDescription = new BLEDescriptor((uint16_t)0x2901); // Characteristic User Description
  DropcontrollerDescription->setValue("Drop Controller");
  BLEDescriptor *NotifyDescripton = new BLE2902(); // Characteristic User Description
  DropControllCharacteristic->addDescriptor(DropcontrollerDescription);
  TimeOffsetCharacteristic->addDescriptor(TimeOffsetDescription);
  NotifyCharacteristic->addDescriptor(NotifyDescripton);
  DropControllCharacteristic->setCallbacks(new DropControllerCallback());
  TimeOffsetCharacteristic->setCallbacks(new TimeOffsetSetCallback());
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void bluetoothTestingConnection()
{
  delay(10);
  // disconnecting
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}