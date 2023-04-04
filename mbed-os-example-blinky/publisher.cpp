#include "iostream"
#include "publisher.h"
#include <exception>

using namespace std;

Publisher::Publisher() : client(&socket) //<<-- Generation of client instance
{
    net = NetworkInterface::get_default_instance();
    isConnected = false;
    //MQTTClient client(&socket); //Generation of client instance
}

void Publisher::Connect(const char* address, uint16_t port, string* clientID, string* username, string* password)
{
    SocketAddress testAddress;

    testAddress.set_ip_address(address); //localhost
    testAddress.set_port(port); //1883

    socket.open(net);
    socket.connect(testAddress);

    connectionData = MQTTPacket_connectData_initializer;
    connectionData.MQTTVersion = 3;
    connectionData.clientID.cstring = (char*) clientID;
    connectionData.username.cstring = (char*) username;
    connectionData.password.cstring = (char*) password;
    client.connect(connectionData);
    isConnected = true;
}

void Publisher::Disconnect()
{
    client.disconnect();
    socket.close();
    /*mosquitto_disconnect(payload);
    mosquitto_destroy(payload);
    mosquitto_lib_cleanup();*/
}

void Publisher::SendTelemetry(float value, float type)
{
    char payload[64];
    sprintf(payload, "Type: %f | Value: %f", type, value);

    MQTT::Message message;
    message.qos = MQTT::QoS::QOS0;
    message.payload = (void*)payload;
    message.payloadlen = strlen((char*)message.payload);
    message.dup = false;
    message.retained = false;

    client.publish("chilli/light", message);

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