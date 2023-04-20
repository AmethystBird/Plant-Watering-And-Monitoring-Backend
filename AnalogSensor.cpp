#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(AnalogIn sensorInterfaceIn, string valueTypeIn, const char* topicIn, chrono::milliseconds readRateIn) : sensorInterfaceType(sensorInterfaceIn) {
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

float AnalogSensor::GetLastValue()
{
    if (currentSensorValue >= 0.f)
    {
        return currentSensorValue;
    }
    else {
        cout << "[WARNING] " << sensorInterfaceType << " last value is empty.\n";
        return -1.f;
    }

    /*if (sensorBuffer.empty())
    {
        cout << "[WARNING] " << sensorInterfaceType << " buffer is empty.\n";
        return 0.f;
    }
    float valueToSend = sensorBuffer.front();
    sensorBuffer.erase(sensorBuffer.begin());
    return valueToSend;*/
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

    currentSensorValue = (float) sensorInterfaceType;

    //float sensorInputValue = (float) sensorInterfaceType;
    //sensorBuffer.push_back(sensorInputValue);
}