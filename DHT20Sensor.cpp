#include "DHT20Sensor.h"

DHT20Sensor::DHT20Sensor(string valueTypeIn, string topicIn, chrono::milliseconds readRateIn) {
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

void DHT20Sensor::AcquireSensorValue()
{
    if (sensorBuffer.size() < 16)
    {
        SensorValueAndMetadata_t currentSensorData;
        if (valueType == "Temperature")
        {
            cout << "Temperature: " << sensorInterfaceType.temperature << "\n\n";
            currentSensorData.sensorValue = (float) sensorInterfaceType.temperature;
        }
        else if (valueType == "Humidity")
        {
            cout << "Humidity: " << sensorInterfaceType.Humidity << "\n\n";
            currentSensorData.sensorValue = (float) sensorInterfaceType.Humidity;
        }
        else
        {
            return;
        }

        time_t valueDateTimeRetrieval = time(0);
        currentSensorData.valueDateTime = ctime(&valueDateTimeRetrieval);
        sensorBuffer.push(currentSensorData);
    }
    else
    {
        cout << "[WARNING] Sensor buffer is full; cannot add any more values" << endl;
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

SensorValueAndMetadata_t DHT20Sensor::GetLastValue()
{
    //vector<Sensor::sensorValueAndMetadata> buff;

    if (sensorBuffer.size() <= 0)
    {
        cout << "[WARNING] Sensor buffer is empty; cannot retrieve any more values" << endl;
        
        sensorValueAndMetadata emptyValues;
        emptyValues.sensorValue = -1;
        emptyValues.valueDateTime = "empty";
        return emptyValues;
        
        //return Sensor::GetRedundantData();
    }

    cout << "Popped value off buffer" << endl;
    SensorValueAndMetadata_t sensorBufferElement = sensorBuffer.front();
    sensorBuffer.pop();
    return sensorBufferElement;
}