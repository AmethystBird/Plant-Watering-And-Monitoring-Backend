#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(AnalogIn sensorInterfaceIn, string valueTypeIn, chrono::milliseconds readRateIn) : sensorInterfaceType(sensorInterfaceIn) {
    valueType = valueTypeIn;
    readRate = readRateIn;

    auto DataString = [this]() {
        cout << "Sensor: " << sensorInterfaceType << "\n";
        this->DisplaySensorValue();
    };

    auto DispatchToQueue = [this]() {
        this->sensorQueue.dispatch_forever();
    };

    updateLoopThread.start(DispatchToQueue);
    sensorQueue.call_every(readRate, DataString);
}

float AnalogSensor::GetLastValue()
{
    if (sensorBuffer.empty())
    {
        cout << "[WARNING] " << sensorInterfaceType << " buffer is empty.\n";
        return 0.f;
    }
    float valueToSend = sensorBuffer.front();
    sensorBuffer.erase(sensorBuffer.begin());
    return valueToSend;
}