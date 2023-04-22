#include "Sensor.h"

float Sensor::GetMockedSensorValue()
{
    int randomValue = rand() % 100;
    float randomDecimalValue = static_cast<float>(randomValue);
    randomDecimalValue = randomDecimalValue / 100.f;
    return randomDecimalValue;
}

/*vector<float>* Sensor::GetUpdatingValues()
{
    return &sensorBuffer;
}*/

string Sensor::GetSensorName()
{
    return valueType;
}

void Sensor::StopSensing()
{
    sensorQueue.break_dispatch();
}

string Sensor::GetTopic()
{
    return topic;
}

void Sensor::SetTopic(string topicIn)
{
    topic = topicIn;
}

unsigned int Sensor::GetSensorBufferSize()
{
    return sensorBuffer.size();
}

/*SensorValueAndMetadata_t Sensor::GetRedundantData()
{
    sensorValueAndMetadata emptyValues;
    emptyValues.sensorValue = -1;
    emptyValues.valueDateTime = "empty";
    return emptyValues;
}*/