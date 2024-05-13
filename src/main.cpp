#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>


#define BLE_SERVER_NAME "BLE-ESP32-Beacon"
#define SERVICE_UUID    "4ff10849-b57e-4761-a6ac-99d00ee5e5c6"


BLEScan     *pBLEScan;
bool deviceConnected = false;


BLECharacteristic BeaconCharacteristics("9a8d7af1-8136-4549-b3f7-d8529ab98ba6", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor BeaconDescriptor(BLEUUID((uint16_t)0x2902));


class BeaconServerCallbacks: public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
    }


    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
    }
};


void setup()
{
    Serial.begin(115200);

    BLEDevice::init(BLE_SERVER_NAME);

    // Setup the ble server
    BLEServer  *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new BeaconServerCallbacks());

    // Setup the service id
    BLEService *beaconService = pServer->createService(SERVICE_UUID);
    beaconService->addCharacteristic(&BeaconCharacteristics);
    BeaconCharacteristics.setValue("Joe joe!");
    BeaconCharacteristics.addDescriptor(&BeaconDescriptor);

    // Start advertising the server
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pServer->getAdvertising()->start();
    Serial.println("Iemand moet hier verbinden lol!");
}


void loop()
{
    if (deviceConnected) {
        Serial.println("Een apparaat is verbonden jeej!");
    }
}
