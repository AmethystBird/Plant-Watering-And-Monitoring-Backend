#include "Sensor.h"

Sensor::Sensor(PinName sensorPinIn, string sensorTypeIn, chrono::milliseconds readRateIn) : sensor(sensorPinIn) {
    sensorType = sensorTypeIn;
    readRate = readRateIn;
}

double Sensor::StartSensing()
{
    if (sensorType == "light")
    {
        while (true)
        {
            DisplaySensorValue("Light Level: ");
            ThisThread::sleep_for(readRate);
        }
    }
    return 0.0;
}

void Sensor::DisplaySensorValue(string sensorDenominator)
{
    cout << sensorDenominator << sensor << "\n";
}