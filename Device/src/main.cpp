#include <Arduino.h>

/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updated by chegewara

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 4fafc201-1fb5-459e-8fcc-c5c9c331914b
   And has a characteristic of: beb5483e-36e1-4688-b7f5-ea07361b26a8

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   A connect hander associated with the server starts a background task that performs notification
   every couple of seconds.
*/
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

BLECharacteristic *pCharacteristic_Points_Team1 = NULL;
BLECharacteristic *pCharacteristic_Points_Team2 = NULL;
BLECharacteristic *pCharacteristic_SummedPoints_Team1 = NULL;
BLECharacteristic *pCharacteristic_SummedPoints_Team2 = NULL;

int value_Points_Team1 = 0;
int value_Points_Team2 = 0;
int value_SummedPoints_Team1 = 0;
int value_SummedPoints_Team2 = 0;

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID "acf4e731-64f4-4c13-b83d-9ea85d92a139"
#define CHARACTERISTIC_UUID "86a6d5ae-048b-41cf-929f-a54a0d900a02"

#define SERVICE_UUID_Game "6ba7b810-9dad-11d1-80b4-00c04fd430c8"
#define CHARACTERISTIC_UUID_Points_Team1 "9b5a6f18-6c76-4f5e-aa5e-c5a5e6d1a42e"
#define CHARACTERISTIC_UUID_Points_Team2 "3f2370b7-6e79-4b16-b9e9-0fcd4b4c6b59"
#define CHARACTERISTIC_UUID_SummedPoints_Team1 "65a6c077-e5f2-4975-9c17-e5f442227c2a"
#define CHARACTERISTIC_UUID_SummedPoints_Team2 "1f30b69a-b3f8-4be3-9cfe-9f9b55d33b19"

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    BLEDevice::startAdvertising();
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

void setup()
{
  Serial.begin(115200);

  // Create the BLE Device
  BLEDevice::init("MatDis BLE");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLEService *pServiceGame = pServer->createService(SERVICE_UUID_Game);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic_Points_Team1 = pServiceGame->createCharacteristic(
      CHARACTERISTIC_UUID_Points_Team1,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic_Points_Team2 = pServiceGame->createCharacteristic(
      CHARACTERISTIC_UUID_Points_Team2,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic_SummedPoints_Team1 = pServiceGame->createCharacteristic(
      CHARACTERISTIC_UUID_SummedPoints_Team1,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);
  pCharacteristic_SummedPoints_Team2 = pServiceGame->createCharacteristic(
      CHARACTERISTIC_UUID_SummedPoints_Team2,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY |
          BLECharacteristic::PROPERTY_INDICATE);

  // pCharacteristic_Points_Team1->setValue("0");
  // pCharacteristic_Points_Team2->setValue("0");
  // pCharacteristic_SummedPoints_Team1->setValue("0");
  // pCharacteristic_SummedPoints_Team2->setValue("0");

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic_Points_Team1->addDescriptor(new BLE2902());
  pCharacteristic_Points_Team2->addDescriptor(new BLE2902());
  pCharacteristic_SummedPoints_Team1->addDescriptor(new BLE2902());
  pCharacteristic_SummedPoints_Team2->addDescriptor(new BLE2902());

  // Start the service
  pService->start();
  pServiceGame->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_UUID_Game);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0); // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop()
{
  // notify changed value
  if (deviceConnected)
  {
    std::string value_Points_Team1 = pCharacteristic_Points_Team1->getValue();
    std::string value_Points_Team2 = pCharacteristic_Points_Team2->getValue();
    std::string value_SummedPoints_Team1 = pCharacteristic_SummedPoints_Team1->getValue();
    std::string value_SummedPoints_Team2 = pCharacteristic_SummedPoints_Team2->getValue();

    pCharacteristic->setValue((uint8_t *)&value, 4);
    pCharacteristic->notify();
    value++;
    pCharacteristic_Points_Team1->setValue((uint8_t *)&value_Points_Team1, 4);
    pCharacteristic_Points_Team2->setValue((uint8_t *)&value_Points_Team2, 4);
    pCharacteristic_SummedPoints_Team1->setValue((uint8_t *)&value_SummedPoints_Team1, 4);
    pCharacteristic_SummedPoints_Team2->setValue((uint8_t *)&value_SummedPoints_Team2, 4);
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
  }
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
