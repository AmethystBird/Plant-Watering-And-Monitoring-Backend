#include "iostream"
#include "publisher.h"

using namespace std;

Publisher::Publisher()
{
    mosquitto_lib_init();

    payload = mosquitto_new("nucleo-publisher", true, NULL); //Generate client instance (null for no authentication requirements)
}

int Publisher::Connect()
{
    int connectionInfo = mosquitto_connect(payload, "localhost", 1883, 60); //Input connection info
    if (connectionInfo != 0) //Check for successful connection
    {
        cout << "Client board unable to connect to broker.\n Error: %d\n", connectionInfo;
        mosquitto_destroy(payload);
        return -1;
    }
    printf("Client board connected to broker.\n");
    return 0;
}

void Publisher::Disconnect()
{
    mosquitto_disconnect(payload);
    mosquitto_destroy(payload);
    mosquitto_lib_cleanup();
}

void Publisher::SendTelemetry()
{
    mosquitto_publish(payload, NULL, "SensorDataTest", 6, "Hello", 0, false); //NULL for no message ID
}

/*
void NetworkDataUpdateLoop(vector<Sensor*>* updatingValuesFromSensors)

for (int i = 0; updatingValuesFromSensors.size(); i++)
        {
            float value = updatingValuesFromSensors[i]->GetLastValue();
            string valueToSend = std::to_string(value);
            messageToSend = messageToSend + valueToSend;
        }

        //float testValue = updatingValuesFromSensors->begin()->GetLastValue();

        float lightValue = updatingValuesFromSensors->operator[](0)->GetLastValue();

        //float lightValue = updatingValuesFromSensors->operator[](0).GetLastValue();
        //float moistureValue = updatingValuesFromSensors->operator[](1).GetLastValue();

        //float lightValue = updatingValuesFromSensors[0].GetLastValue();
        //float temperatureValue = updatingValuesFromSensors[1].GetLastValue();
        //float humidityValue = updatingValuesFromSensors[2].GetLastValue();
        //float moistureValue = updatingValuesFromSensors[3].GetLastValue();

        //sprintf(message, "{ \"Light\" : %5.2f, \"Temperature\" : %5.2f, \"Humidity\" : %5.2f, \"Moisture\" : %5.2f }", lightValue, temperatureValue, humidityValue, moistureValue);
        sprintf(message, "{ \"Light\" : %5.2f }", lightValue);
*/