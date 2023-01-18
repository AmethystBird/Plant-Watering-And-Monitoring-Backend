#include "Sensor.h"

Sensor::Sensor(PinName sensorPinIn, string sensorTypeIn, chrono::milliseconds readRateIn) : sensorInput(sensorPinIn) {
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
        cout << "Sensor: " << sensorType << "\n";
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
    if (sensorType == "Temperature and Humidity")
    {
        float mockedTemperatureValue = GetMockedSensorValue();
        float mockedHumidityValue = GetMockedSensorValue();

        cout << "Temperature: (Mocked)" << mockedTemperatureValue << "\n";
        cout << "Humidity: (Mocked)" << mockedHumidityValue << "\n\n";
    }
    else if (sensorType == "Moisture")
    {
        float randomMoistureValue = GetMockedSensorValue();
        cout << "Moisture: (Mocked)" << randomMoistureValue << "\n\n";
    }
    else if (sensorType == "Light")
    {
        cout << "Light: " << sensorInput << "\n\n";
    }
}

float Sensor::GetMockedSensorValue()
{
    int randomValue = rand() % 100;
    float randomDecimalValue = static_cast<float>(randomValue);
    randomDecimalValue = randomDecimalValue / 100.f;
    return randomDecimalValue;
}