#include "Sensor.h"

Sensor::Sensor(PinName sensorPinIn, string sensorTypeIn, chrono::milliseconds readRateIn) : sensor(sensorPinIn) {
    sensorType = sensorTypeIn;
    readRate = readRateIn;
    isSensing = false;
}

void Sensor::StartSensing()
{
    isSensing = true;
    updateLoopThread.start(callback(this, &Sensor::UpdateLoop));
}

void Sensor::UpdateLoop()
{
    while (isSensing)
    {
        cout << sensorType << " Level: ";
        DisplaySensorValue();
        ThisThread::sleep_for(readRate);
    }
    updateLoopThread.join();
}

void Sensor::StopSensing()
{
    isSensing = false;
}

void Sensor::DisplaySensorValue()
{
    cout << sensor << "\n";
}