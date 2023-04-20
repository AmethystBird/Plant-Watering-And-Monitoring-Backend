#include "MQTTPlantClient.h"

EthernetInterface net;

MQTTPlantClient::MQTTPlantClient() : client(&socket)
{
    isConnected = false;
}

bool MQTTPlantClient::Connect(string address, uint16_t port)
{
    net.connect(); //Connects ethernet

    nsapi_error_t errorCode = net.get_ip_address(&a); //Acquiring IP address
    if (errorCode != NSAPI_ERROR_OK)
    {
        cout << "MQTTPlantClient | Connect(): Unable to get IP address" << endl;
        return false;
    }
    else
    {
        cout << "MQTTPlantClient | Connect(): IP Address obtained: " << a.get_ip_address() << endl;
    }

    //Opens network interface socket
    errorCode = socket.open(&net);
    if (errorCode != NSAPI_ERROR_OK)
    {
        cout << "MQTTPlantClient | Connect(): Unable to open TCP socket" << endl;
        return false;
    }
    else
    {
        cout << "MQTTPlantClient | Connect(): TCP socked opened" << endl;
    }

    //Provisional
    //net.gethostbyname("test.mosquitto.org", &a);
    //printf("Server IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    //Sets TCP socket address
    bool IPIsSet = a.set_ip_address(address.c_str());
    if (!IPIsSet)
    {
        cout << "MQTTPlantClient | Connect(): Unable to set IP address" << endl;
        return false;
    }
    else
    {
        cout << "MQTTPlantClient | Connect(): IP address set" << endl;
    }

    a.set_port(port); //Sets TCP socket port

    //Connects to server
    errorCode = socket.connect(a);
    if (errorCode != NSAPI_ERROR_OK)
    {
        cout << "MQTTPlantClient | Connect(): Socket unable to connect to server" << endl;
        return false;
    }
    else
    {
        cout << "MQTTPlantClient | Connect(): Socket connected to server" << endl;
    }
    return true;
}

void MQTTPlantClient::Authenticate(string clientID, string username, string password)
{   
    connectionData = MQTTPacket_connectData_initializer;
    connectionData.MQTTVersion = 3;
    connectionData.clientID.cstring = (char*)clientID.c_str();
    connectionData.username.cstring = (char*)username.c_str();
    connectionData.password.cstring = (char*)password.c_str();
    nsapi_error_t errorCode = client.connect(connectionData);

    if (errorCode != NSAPI_ERROR_OK)
    {
        cout << "MQTTPlantClient | Authenticate(): Unable to connect to server" << endl;
    }
    else
    {
        cout << "MQTTPlantClient | Authenticate(): Connected to server" << endl;
    }
}

void MQTTPlantClient::Disconnect()
{
    client.disconnect();
    socket.close();
    net.disconnect();
    isConnected = false;
}

bool MQTTPlantClient::GetIsConnected()
{
    return isConnected;
}

void MQTTPlantClient::SetIsConnected(bool isConnectedIn, string address, uint16_t port)
{
    if (isConnectedIn == true && isConnected == false)
    {
        if (Connect(address, port) == true)
        {
            isConnected = true;
        }
    }
    else if (isConnectedIn == false && isConnected == true)
    {
        Disconnect();
    }
    else
    {
        cout << "MQTTPlantClient | SetIsConnected(): An attempt was made either to connect while connected, or vice versa. This is implausible.";
    }
}

void MQTTPlantClient::Publish(const char* topic, float telemetryType, float telemetryValue)
{
    char payload[64];
    cout << "MQTTPlantClient | Publish(): " << payload << " | Type: " << telemetryType << " | Value: " << telemetryValue << endl;

    sprintf(payload, "%f", telemetryValue);

    MQTT::Message message;
    message.qos = MQTT::QoS::QOS0;
    message.payload = (void*)payload;
    message.payloadlen = strlen((char*)message.payload);
    message.dup = false;
    message.retained = false;

    client.publish(topic, message);
    cout << "PUBLISHED MESSAGE" << endl;
}