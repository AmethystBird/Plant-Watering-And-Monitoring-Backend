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

const char* Sensor::GetTopic()
{
    return topic;
}

void Sensor::SetTopic(const char* topicIn)
{
    topic = topicIn;
}