#include "Sensor.h"

void Sensor::DisplaySensorValue()
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
        cout << "Light: " << sensorInterfaceType << "\n\n";
        
        float sensorInputValue = (float) sensorInterfaceType;
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

string Sensor::GetSensorName()
{
    return sensorName;
}