#include "DHT20Sensor.h"

DHT20Sensor::DHT20Sensor(DHT20 sensorInterfaceIn, string valueTypeIn, chrono::milliseconds readRateIn) {
    sensorInterfaceType = sensorInterfaceIn.readTemperatureAndHumidity();
    valueType = valueTypeIn;
    readRate = readRateIn;

    auto DataString = [this, valueTypeIn]() {
        if (valueType == "Temperature")
        {
            cout << "Sensor: " << sensorInterfaceType.temperature << "\n";
        }
        else if (valueType == "Humidity")
        {
            cout << "Sensor: " << sensorInterfaceType.Humidity << "\n";
        }
        DisplaySensorValue();
    };

    auto DispatchToQueue = [this]() {
        this->sensorQueue.dispatch_forever();
    };

    updateLoopThread.start(DispatchToQueue);
    sensorQueue.call_every(readRate, DataString);
}

float DHT20Sensor::GetLastValue()
{
    if (sensorBuffer.empty())
    {
        if (valueType == "Temperature")
        {
            cout << "[WARNING] " << sensorInterfaceType.temperature << " buffer is empty.\n";
        }
        else if (valueType == "Humidity")
        {
            cout << "[WARNING] " << sensorInterfaceType.Humidity << " buffer is empty.\n";
        }
        return 0.f;
    }
    float valueToSend = sensorBuffer.front();
    sensorBuffer.erase(sensorBuffer.begin());
    return valueToSend;
}

void DHT20Sensor::DisplaySensorValue()
{
    if (valueType == "Temperature")
    {
        float mockedTemperatureValue = GetMockedSensorValue();

        cout << "Temperature: (Mocked)" << mockedTemperatureValue << "\n";

        sensorBuffer.push_back(mockedTemperatureValue);
    }
    else if (valueType == "Humidity")
    {
        float mockedHumidityValue = GetMockedSensorValue();

        cout << "Humidity: (Mocked)" << mockedHumidityValue << "\n\n";

        sensorBuffer.push_back(mockedHumidityValue);
    }
}

const char* DHT20Sensor::GetTopic()
{
    return topic;
}

void DHT20Sensor::SetTopic(const char* topicIn)
{
    topic = topicIn;
}

const char* DHT20Sensor::GetTopic2()
{
    return topic2;
}

void DHT20Sensor::SetTopic2(const char* topic2In)
{
    topic2 = topic2In;
}