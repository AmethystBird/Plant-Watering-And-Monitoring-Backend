#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(PinName sensorInterfaceIn_Pin, string valueTypeIn, string topicIn, chrono::milliseconds readRateIn) : sensorInterfaceType(sensorInterfaceIn_Pin) {
    valueType = valueTypeIn;
    topic = topicIn;
    readRate = readRateIn;

    auto DataString = [this]() {
        cout << "Sensor: " << sensorInterfaceType << "\n";
        AcquireSensorValue();
    };

    auto DispatchToQueue = [this]() {
        this->sensorQueue.dispatch_forever();
    };

    updateLoopThread.start(DispatchToQueue);
    sensorQueue.call_every(readRate, DataString);
}

void AnalogSensor::AcquireSensorValue()
{
    if (valueType == "Moisture")
    {
        cout << "Moisture";
    }
    else if (valueType == "Light")
    {
        cout << "Light";
    }
    else
    {
        return;
    }

    cout << ": " << sensorInterfaceType << "\n\n";

    if (sensorBuffer.size() < 16)
    {
        SensorValueAndMetadata_t currentSensorData;
        currentSensorData.sensorValue = (float) sensorInterfaceType;

        /*time_t valueDateTimeRetrieval = time(0);
        currentSensorData.valueDateTime = ctime(&valueDateTimeRetrieval);
        sensorBuffer.push(currentSensorData);*/

        time_t valueDateTimeRetrieval = time(0);
        tm* valueDateTimeInfo = localtime(&valueDateTimeRetrieval);
        int hours = valueDateTimeInfo->tm_hour;
        int minutes = valueDateTimeInfo->tm_min;
        int seconds = valueDateTimeInfo->tm_sec;

        string timeToSend = "H: " + std::to_string(hours) + " M: " + std::to_string(minutes) + " S: " + std::to_string(seconds);

        //currentSensorData.valueDateTime = ctime(&valueDateTimeRetrieval);
        currentSensorData.valueDateTime = timeToSend;
        sensorBuffer.push(currentSensorData);
    }
    else
    {
        cout << "[WARNING] Sensor buffer is full; cannot add any more values" << endl;
    }

    //float sensorInputValue = (float) sensorInterfaceType;
    //sensorBuffer.push_back(sensorInputValue);
}

SensorValueAndMetadata_t AnalogSensor::GetLastValue()
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