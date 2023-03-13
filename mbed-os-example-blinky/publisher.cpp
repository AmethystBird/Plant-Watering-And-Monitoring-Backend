#include "iostream"
#include "publisher.h"

using namespace std;

Publisher::Publisher()
{
    net = NetworkInterface::get_default_instance();
    MQTTClient client(&socket); //Generation of client instance
}

int Publisher::Connect(const char* address, uint16_t port)
{
    SocketAddress testAddress;
    testAddress.set_ip_address(address); //localhost
    testAddress.set_port(port); //1883

    socket.open(net);
    socket.connect(testAddress);
}

void Publisher::Disconnect()
{
    socket.close();
    /*mosquitto_disconnect(payload);
    mosquitto_destroy(payload);
    mosquitto_lib_cleanup();*/
}

void Publisher::SendTelemetry()
{
    //mosquitto_publish(payload, NULL, "SensorDataTest", 6, "Hello", 0, false); //NULL for no message ID
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