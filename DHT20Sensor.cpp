#include "DHT20Sensor.h"

DHT20Sensor::DHT20Sensor(string valueTypeIn, const char* topicIn, chrono::milliseconds readRateIn) {
    sensorInterfaceType = DHT20SensorLib.readTemperatureAndHumidity();
    valueType = valueTypeIn;
    topic = topicIn;
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
        AcquireSensorValue();
    };

    auto DispatchToQueue = [this]() {
        this->sensorQueue.dispatch_forever();
    };

    updateLoopThread.start(DispatchToQueue);
    sensorQueue.call_every(readRate, DataString);
}

float DHT20Sensor::GetLastValue()
{
    if (currentSensorValue >= 0.f)
    {
        return currentSensorValue;
    }
    else
    {
        if (valueType == "Temperature")
        {
            cout << "[WARNING] " << sensorInterfaceType.temperature << " last value is empty.\n";
        }
        else if (valueType == "Temperature")
        {
            cout << "[WARNING] " << sensorInterfaceType.Humidity << " last value is empty.\n";
        }
        return -1.f;
    }

    /*if (sensorBuffer.empty())
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
    return valueToSend;*/
}

void DHT20Sensor::AcquireSensorValue()
{
    if (valueType == "Temperature")
    {
        cout << "Temperature: " << sensorInterfaceType.temperature << "\n\n";
        currentSensorValue = (float) sensorInterfaceType.temperature;
    }
    else if (valueType == "Humidity")
    {
        cout << "Humidity: " << sensorInterfaceType.Humidity << "\n\n";
        currentSensorValue = (float) sensorInterfaceType.Humidity;
    }
    else
    {
        return;
    }

    /*if (valueType == "Temperature")
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
    }*/
}