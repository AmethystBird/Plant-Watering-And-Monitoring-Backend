#include "Sensor.h"

template <class sensorPin>
Sensor<sensorPin>::Sensor(sensorPin sensorPinIn, string sensorNameIn, chrono::milliseconds readRateIn) : sensorType(sensorPinIn) {
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

template <class sensorPin>
void Sensor<sensorPin>::StopSensing()
{
    isSensing = false;
}

template <class sensorPin>
void Sensor<sensorPin>::DisplaySensorValue()
{
    if (sensorName == "Temperature" || "Humidity")
    {
        if (sensorName == "Temperature")
        {
            float mockedTemperatureValue = GetMockedSensorValue();

            cout << "Temperature: (Mocked)" << mockedTemperatureValue << "\n";

            sensorBuffer.push_back(mockedTemperatureValue);
        }
        else if (sensorName == "Humidity")
        {
            float mockedHumidityValue = GetMockedSensorValue();

            cout << "Humidity: (Mocked)" << mockedHumidityValue << "\n\n";

            sensorBuffer.push_back(mockedHumidityValue);
        }
    }
    else if (sensorName == "Moisture")
    {
        float randomMoistureValue = GetMockedSensorValue();
        cout << "Moisture: (Mocked)" << randomMoistureValue << "\n\n";
        sensorBuffer.push_back(randomMoistureValue);
    }
    else if (sensorName == "Light")
    {
        cout << "Light: " << sensorType << "\n\n";
        
        float sensorInputValue = (float) sensorType;
        sensorBuffer.push_back(sensorInputValue);
    }
}

template <class sensorPin>
float Sensor<sensorPin>::GetMockedSensorValue()
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

template <class sensorPin>
vector<float>* Sensor<sensorPin>::GetUpdatingValues()
{
    return &sensorBuffer;
}

template <class sensorPin>
float Sensor<sensorPin>::GetLastValue()
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

template <class sensorPin>
string Sensor<sensorPin>::GetSensorName()
{
    return sensorName;
}