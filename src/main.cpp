#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>


BLEScan *pBLEScan;


class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        Serial.printf("Advertised Device: %s\n", advertisedDevice.toString().c_str());
    }
};


void setup()
{
    Serial.begin(115200);

    BLEDevice::init("");

    pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true);
    pBLEScan->start(30);
}


void loop()
{
    
}
