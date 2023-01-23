#include "Sensor.h"

template <class sensorPin>
Sensor<sensorPin>::Sensor(PinName sensorPinIn, string sensorNameIn, chrono::milliseconds readRateIn) : sensorType(sensorPinIn) {
    sensorName = sensorNameIn;
    readRate = readRateIn;
    isSensing = false;

    auto DataString = [this]() {
        cout << "Sensor: " << sensorType << "\n";
        this->DisplaySensorValue();
    };

    auto DispatchToQueue = [this]() {
        this->sensorQueue.dispatch_forever();
    };

    updateLoopThread.start(DispatchToQueue);
    sensorQueue.call_every(readRate, DataString);
}

/*void Sensor::StartSensing()
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
}*/

void Sensor::StopSensing()
{
    isSensing = false;
}

void Sensor::DisplaySensorValue()
{
    if (sensorType == "Temperature" || "Humidity")
    {
        if (sensorType == "Temperature")
        {
            float mockedTemperatureValue = GetMockedSensorValue();

            cout << "Temperature: (Mocked)" << mockedTemperatureValue << "\n";

            sensorBuffer.push_back(mockedTemperatureValue);
        }
        else if (sensorType == "Humidity")
        {
            float mockedHumidityValue = GetMockedSensorValue();

            cout << "Humidity: (Mocked)" << mockedHumidityValue << "\n\n";

            sensorBuffer.push_back(mockedHumidityValue);
        }
    }
    else if (sensorType == "Moisture")
    {
        float randomMoistureValue = GetMockedSensorValue();
        cout << "Moisture: (Mocked)" << randomMoistureValue << "\n\n";
        sensorBuffer.push_back(randomMoistureValue);
    }
    else if (sensorType == "Light")
    {
        cout << "Light: " << sensorInput << "\n\n";
        
        float sensorInputValue = (float) sensorInput;
        sensorBuffer.push_back(sensorInputValue);
    }
}

float Sensor::GetMockedSensorValue()
{
    int randomValue = rand() % 100;
    float randomDecimalValue = static_cast<float>(randomValue);
    randomDecimalValue = randomDecimalValue / 100.f;
    return randomDecimalValue;
}

/*float* Sensor::GetUpdatingValues()
{
    return sensorBuffer.data();
}*/

vector<float>* Sensor::GetUpdatingValues()
{
    return &sensorBuffer;
}

float Sensor::GetLastValue()
{
    if (sensorBuffer.empty())
    {
        cout << "[WARNING] " << sensorType << " buffer is empty.\n";
        return 0.f;
    }
    float valueToSend = sensorBuffer.front();
    sensorBuffer.erase(sensorBuffer.begin());
    return valueToSend;
}

string Sensor::GetSensorType()
{
    return sensorType;
}