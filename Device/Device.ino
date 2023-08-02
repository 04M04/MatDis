//created by 04M04
//VERSION v1.0.4

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// #define SERIAL_BAUD 115200
#define DEVICE_NAME "MATDIS BLE"
#define VERSION "v1.0.4"
#define MODEL "MATDIS v1"
#define DEVELOPER "04M04"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic_Model = NULL;
BLECharacteristic *pCharacteristic_Version = NULL;
BLECharacteristic *pCharacteristic_Developer = NULL;

BLECharacteristic *pCharacteristic_Brightness = NULL;

BLECharacteristic *pCharacteristic_Points_Team1 = NULL;
BLECharacteristic *pCharacteristic_Points_Team2 = NULL;
BLECharacteristic *pCharacteristic_SummedPoints_Team1 = NULL;
BLECharacteristic *pCharacteristic_SummedPoints_Team2 = NULL;

#define SERVICE_UUID_Infos "b4d964fe-3303-4a98-b9b3-490e08371424"
#define CHARACTERISTIC_UUID_Model "17d5dbf1-6743-47ab-8060-657b36c86984"
#define CHARACTERISTIC_UUID_Version "5641f4d2-97a6-481f-9fa4-34e967fd394d"
#define CHARACTERISTIC_UUID_Developer "68f8edca-7c50-46d5-b593-e16d33d10ae8"

#define SERVICE_UUID_Settings "2a630f38-f28b-4645-bc6e-a608d123d9ea"
#define CHARACTERISTIC_UUID_Brightness "1b9c30d8-7811-4b01-b995-29241a40bde4"

#define SERVICE_UUID_Game "6ba7b810-9dad-11d1-80b4-00c04fd430c8"
#define CHARACTERISTIC_UUID_Points_Team1 "9b5a6f18-6c76-4f5e-aa5e-c5a5e6d1a42e"
#define CHARACTERISTIC_UUID_Points_Team2 "3f2370b7-6e79-4b16-b9e9-0fcd4b4c6b59"
#define CHARACTERISTIC_UUID_SummedPoints_Team1 "65a6c077-e5f2-4975-9c17-e5f442227c2a"
#define CHARACTERISTIC_UUID_SummedPoints_Team2 "1f30b69a-b3f8-4be3-9cfe-9f9b55d33b19"

bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

int brightness = 3; // 0 - 255

int team1_points = 0; // 00 - 99
int team2_points = 0; // 00 - 99
int team1_summedPoints = 0; // 00 - 99
int team2_summedPoints = 0; // 00 - 99

int pwmChannel = 0; // Selects channel 0
int frequence = 2100000; //24 KHz // PWM frequency of 1 KHz
int resolution = 8; // 8-bit resolution, 256 possible values

#include <DMD32.h>
#include "fonts/myFont_16x16.h"
#include "fonts/myFont_16x32.h"

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 3
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

//Timer setup
//create a hardware timer  of ESP32
hw_timer_t * timer = NULL;

//buttons
//--------------------------------------------------------------------------------------
int BTN_RESET_TEAM1_POINTS_PIN = 34;
int BTN_ADD_TEAM1_POINTS_PIN = 35;
int BTN_SUB_TEAM1_POINTS_PIN = 32;
int BTN_RESET_TEAM2_POINTS_PIN = 33;
int BTN_ADD_TEAM2_POINTS_PIN = 25;
int BTN_SUB_TEAM2_POINTS_PIN = 26;
int BTN_RESET_TEAM1_PLAYS_PIN = 27;
int BTN_ADD_TEAM1_PLAYS_PIN = 14;
int BTN_SUB_TEAM1_PLAYS_PIN = 12;
int BTN_RESET_TEAM2_PLAYS_PIN = 17;
int BTN_ADD_TEAM2_PLAYS_PIN = 16;
int BTN_SUB_TEAM2_PLAYS_PIN = 4;

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;
unsigned long last_button_time = 0;
#define debounceDelay 250  // the debounce time; increase if the output flickers

int last_btnPressedState = 0;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
  ledcWrite(pwmChannel, brightness);
}

void drawCount(int team1_points, int team2_points, int team1_summedPoints, int team2_summedPoints)
{
  char buffer[100];

  dmd.selectFont(myFont_16x32);

  sprintf(buffer, "%02d", team1_points);
  dmd.drawChar( 0, 0, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(16, 0, buffer[1], GRAPHICS_NORMAL );
  sprintf(buffer, "%02d", team2_points);
  dmd.drawChar(32, 0, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(48, 0, buffer[1], GRAPHICS_NORMAL );

  dmd.selectFont(myFont_16x16);
  
  sprintf(buffer, "%02d", team1_summedPoints);
  dmd.drawChar( 0, 32, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(16, 32, buffer[1], GRAPHICS_NORMAL );
  sprintf(buffer, "%02d", team2_summedPoints);
  dmd.drawChar(32, 32, buffer[0], GRAPHICS_NORMAL );
  dmd.drawChar(48, 32, buffer[1], GRAPHICS_NORMAL );
}

void brightness_setup()
{
  ledcSetup(pwmChannel, frequence, resolution);
  ledcAttachPin(PIN_DMD_nOE, pwmChannel);
  ledcWrite(pwmChannel, brightness);
}

void dmd_setup()
{
  // return the clock speed of the CPU
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  
  // Use 1st timer of 4 
  // devide cpu clock speed on its speed value by MHz to get 1us for each signal  of the timer
  timer = timerBegin(0, cpuClock, true);
  // Attach triggerScan function to our timer 
  timerAttachInterrupt(timer, &triggerScan, true);
  // Set alarm to call triggerScan function  
  // Repeat the alarm (third parameter) 
  timerAlarmWrite(timer, 300, true);

  // Start an alarm 
  timerAlarmEnable(timer);

   //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
}

void IRAM_ATTR trigger_BTN_RESET_TEAM1_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM1_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM1_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM1_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM1_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM1_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_RESET_TEAM2_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM2_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM2_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM2_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM2_POINTS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM2_POINTS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_RESET_TEAM1_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM1_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM1_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM1_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM1_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM1_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_RESET_TEAM2_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_RESET_TEAM2_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_ADD_TEAM2_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_ADD_TEAM2_PLAYS_PIN;
    last_button_time = button_time;
  }
}
void IRAM_ATTR trigger_BTN_SUB_TEAM2_PLAYS_PIN(){
  button_time = millis();
  if (button_time - last_button_time > debounceDelay)
  {
    last_btnPressedState = BTN_SUB_TEAM2_PLAYS_PIN;
    last_button_time = button_time;
  }
}

void btn_setup()
{
  pinMode(BTN_RESET_TEAM1_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM1_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM1_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_RESET_TEAM2_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM2_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM2_POINTS_PIN, INPUT_PULLUP);
  pinMode(BTN_RESET_TEAM1_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM1_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM1_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_RESET_TEAM2_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_ADD_TEAM2_PLAYS_PIN, INPUT_PULLUP);
  pinMode(BTN_SUB_TEAM2_PLAYS_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM1_POINTS_PIN), trigger_BTN_RESET_TEAM1_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM1_POINTS_PIN), trigger_BTN_ADD_TEAM1_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM1_POINTS_PIN), trigger_BTN_SUB_TEAM1_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM2_POINTS_PIN), trigger_BTN_RESET_TEAM2_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM2_POINTS_PIN), trigger_BTN_ADD_TEAM2_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM2_POINTS_PIN), trigger_BTN_SUB_TEAM2_POINTS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM1_PLAYS_PIN), trigger_BTN_RESET_TEAM1_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM1_PLAYS_PIN), trigger_BTN_ADD_TEAM1_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM1_PLAYS_PIN), trigger_BTN_SUB_TEAM1_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_RESET_TEAM2_PLAYS_PIN), trigger_BTN_RESET_TEAM2_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_ADD_TEAM2_PLAYS_PIN), trigger_BTN_ADD_TEAM2_PLAYS_PIN, FALLING);
  attachInterrupt(digitalPinToInterrupt(BTN_SUB_TEAM2_PLAYS_PIN), trigger_BTN_SUB_TEAM2_PLAYS_PIN, FALLING);
}

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

class MySettingsCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    uint8_t data = pCharacteristic->getValue()[0];
    String id = pCharacteristic->getUUID().toString().c_str();
    if(id == CHARACTERISTIC_UUID_Brightness){
      if(data < 0){
        brightness = 0;
      }
      else if(data > 255){
        brightness = 255;
      }
      else{
        brightness = data;
      }
      pCharacteristic_Brightness->setValue((uint8_t *)&brightness, 1);
      pCharacteristic_Brightness->notify();
    }
  }
};

class MyPointsCharacteristicCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    uint8_t data = pCharacteristic->getValue()[0];
    String id = pCharacteristic->getUUID().toString().c_str();
    if(id == CHARACTERISTIC_UUID_Points_Team1){
      if(data < 0){
        team1_points = 0;
      }
      else if(data > 99){
        team1_points = 99;
      }
      else{
        team1_points = data;
      }
      pCharacteristic_Points_Team1->setValue((uint8_t *)&team1_points, 1);
      pCharacteristic_Points_Team1->notify();
    }
    else if(id == CHARACTERISTIC_UUID_Points_Team2){
      if(data < 0){
        team2_points = 0;
      }
      else if(data > 99){
        team2_points = 99;
      }
      else{
        team2_points = data;
      }
      pCharacteristic_Points_Team2->setValue((uint8_t *)&team2_points, 1);
      pCharacteristic_Points_Team2->notify();
    }
    else if(id == CHARACTERISTIC_UUID_SummedPoints_Team1){
      if(data < 0){
        team1_summedPoints = 0;
      }
      else if(data > 99){
        team1_summedPoints = 99;
      }
      else{
        team1_summedPoints = data;
      }
      pCharacteristic_SummedPoints_Team1->setValue((uint8_t *)&team1_summedPoints, 1);
      pCharacteristic_SummedPoints_Team1->notify();
    }
    else if(id == CHARACTERISTIC_UUID_SummedPoints_Team2){
      if(data < 0){
        team2_summedPoints = 0;
      }
      else if(data > 99){
        team2_summedPoints = 99;
      }
      else{
        team2_summedPoints = data;
      }
      pCharacteristic_SummedPoints_Team2->setValue((uint8_t *)&team2_summedPoints, 1);
      pCharacteristic_SummedPoints_Team2->notify();
    }
    // Serial.println("*********");
    // Serial.print("from UUID: ");
    // Serial.println(id);
    // Serial.print("New value: ");
    // Serial.println(data);
    // Serial.println("*********");
  }
};

void ble_setup()
{
  // Serial.begin(SERIAL_BAUD);

  // Create the BLE Device
  BLEDevice::init(DEVICE_NAME);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pServiceInfos = pServer->createService(SERVICE_UUID_Infos);
  BLEService *pServiceSettings = pServer->createService(SERVICE_UUID_Settings);
  BLEService *pServiceGame = pServer->createService(SERVICE_UUID_Game);

  // Create a BLE Characteristic
  pCharacteristic_Model = pServiceInfos->createCharacteristic(
      CHARACTERISTIC_UUID_Model,
      BLECharacteristic::PROPERTY_READ);
  pCharacteristic_Version = pServiceInfos->createCharacteristic(
      CHARACTERISTIC_UUID_Version,
      BLECharacteristic::PROPERTY_READ);
  pCharacteristic_Developer = pServiceInfos->createCharacteristic(
      CHARACTERISTIC_UUID_Developer,
      BLECharacteristic::PROPERTY_READ);

  pCharacteristic_Brightness = pServiceSettings->createCharacteristic(
      CHARACTERISTIC_UUID_Brightness,
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
  pCharacteristic_Model->addDescriptor(new BLE2902());
  pCharacteristic_Version->addDescriptor(new BLE2902());
  pCharacteristic_Developer->addDescriptor(new BLE2902());
  
  pCharacteristic_Model->setValue((uint8_t *)&MODEL,sizeof(MODEL));
  pCharacteristic_Version->setValue((uint8_t *)&VERSION,sizeof(VERSION));
  pCharacteristic_Developer->setValue((uint8_t *)&DEVELOPER,sizeof(DEVELOPER));



  pCharacteristic_Brightness->addDescriptor(new BLE2902());

  pCharacteristic_Brightness->setCallbacks(new MySettingsCharacteristicCallbacks());

  pCharacteristic_Brightness->setValue((uint8_t *)&brightness, 1);



  pCharacteristic_Points_Team1->addDescriptor(new BLE2902());
  pCharacteristic_Points_Team2->addDescriptor(new BLE2902());
  pCharacteristic_SummedPoints_Team1->addDescriptor(new BLE2902());
  pCharacteristic_SummedPoints_Team2->addDescriptor(new BLE2902());

  pCharacteristic_Points_Team1->setCallbacks(new MyPointsCharacteristicCallbacks());
  pCharacteristic_Points_Team2->setCallbacks(new MyPointsCharacteristicCallbacks());
  pCharacteristic_SummedPoints_Team1->setCallbacks(new MyPointsCharacteristicCallbacks());
  pCharacteristic_SummedPoints_Team2->setCallbacks(new MyPointsCharacteristicCallbacks());

  pCharacteristic_Points_Team1->setValue((uint8_t *)&team1_points, 1);
  pCharacteristic_Points_Team2->setValue((uint8_t *)&team2_points, 1);
  pCharacteristic_SummedPoints_Team1->setValue((uint8_t *)&team1_summedPoints, 1);
  pCharacteristic_SummedPoints_Team2->setValue((uint8_t *)&team2_summedPoints, 1);

  // Start the service
  pServiceInfos->start();
  pServiceSettings->start();
  pServiceGame->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID_Infos);
  pAdvertising->addServiceUUID(SERVICE_UUID_Settings);
  pAdvertising->addServiceUUID(SERVICE_UUID_Game);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0); // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();

  // Serial.println("Waiting a client connection to notify...");
}

void setup()
{
  ble_setup();
  dmd_setup();
  brightness_setup();
  btn_setup();
}

void btn_loop()
{
  //Team 1 points--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM1_POINTS_PIN) {
    team1_points = 0;
    pCharacteristic_Points_Team1->setValue((uint8_t *)&team1_points, 1);
    pCharacteristic_Points_Team1->notify();
  }
  if (last_btnPressedState == BTN_ADD_TEAM1_POINTS_PIN) {
    if (team1_points < 99){
      team1_points++;
      pCharacteristic_Points_Team1->setValue((uint8_t *)&team1_points, 1);
      pCharacteristic_Points_Team1->notify();
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM1_POINTS_PIN) {
    if (team1_points > 0){
      team1_points--;
      pCharacteristic_Points_Team1->setValue((uint8_t *)&team1_points, 1);
      pCharacteristic_Points_Team1->notify();
    }
  }
  //Team 2 points--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM2_POINTS_PIN) {
    team2_points = 0;
    pCharacteristic_Points_Team2->setValue((uint8_t *)&team2_points, 1);
    pCharacteristic_Points_Team2->notify();
  }
  if (last_btnPressedState == BTN_ADD_TEAM2_POINTS_PIN) {
    if (team2_points < 99){
      team2_points++;
      pCharacteristic_Points_Team2->setValue((uint8_t *)&team2_points, 1);
      pCharacteristic_Points_Team2->notify();
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM2_POINTS_PIN) {
    if (team2_points > 0){
      team2_points--;
      pCharacteristic_Points_Team2->setValue((uint8_t *)&team2_points, 1);
      pCharacteristic_Points_Team2->notify();
    }
  }
  //Team 1 plays--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM1_PLAYS_PIN) {
    team1_summedPoints = 0;
    pCharacteristic_SummedPoints_Team1->setValue((uint8_t *)&team1_summedPoints, 1);
    pCharacteristic_SummedPoints_Team1->notify();
  }
  if (last_btnPressedState == BTN_ADD_TEAM1_PLAYS_PIN) {
    if (team1_summedPoints < 99){
      team1_summedPoints++;
      pCharacteristic_SummedPoints_Team1->setValue((uint8_t *)&team1_summedPoints, 1);
      pCharacteristic_SummedPoints_Team1->notify();
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM1_PLAYS_PIN) {
    if (team1_summedPoints > 0){
      team1_summedPoints--;
      pCharacteristic_SummedPoints_Team1->setValue((uint8_t *)&team1_summedPoints, 1);
      pCharacteristic_SummedPoints_Team1->notify();
    }
  }
  //Team 2 plays--------------------------------------------------
  if (last_btnPressedState == BTN_RESET_TEAM2_PLAYS_PIN) {
    team2_summedPoints = 0;
    pCharacteristic_SummedPoints_Team2->setValue((uint8_t *)&team2_summedPoints, 1);
    pCharacteristic_SummedPoints_Team2->notify();
  }
  if (last_btnPressedState == BTN_ADD_TEAM2_PLAYS_PIN) {
    if (team2_summedPoints < 99){
      team2_summedPoints++;
      pCharacteristic_SummedPoints_Team2->setValue((uint8_t *)&team2_summedPoints, 1);
      pCharacteristic_SummedPoints_Team2->notify();
    }
  }
  if (last_btnPressedState == BTN_SUB_TEAM2_PLAYS_PIN) {
    if (team2_summedPoints > 0){
      team2_summedPoints--;
      pCharacteristic_SummedPoints_Team2->setValue((uint8_t *)&team2_summedPoints, 1);
      pCharacteristic_SummedPoints_Team2->notify();
    }
  }

  last_btnPressedState = 0;
}

void ble_loop()
{
  // notify changed value
  if (deviceConnected)
  {
    // pCharacteristic->setValue((uint8_t *)&value, 4);
    // pCharacteristic->notify();
    // value++;
    
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // give the bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // restart advertising
    // Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}

// void pointsSerialOut_loop()
// {
//   Serial.println();
//   Serial.println("team1_points:");
//   Serial.println(team1_points);
//   Serial.println("team2_points:");
//   Serial.println(team2_points);
//   Serial.println("team1_summedPoints:");
//   Serial.println(team1_summedPoints);
//   Serial.println("team2_summedPoints:");
//   Serial.println(team2_summedPoints);
// }

void loop()
{
  btn_loop();
  ble_loop();
  // pointsSerialOut_loop();
  drawCount(team1_points, team2_points, team1_summedPoints, team2_summedPoints);
  // ledcWrite(pwmChannel, brightness);
}
