#pragma once

#include "mbed.h"
#include <MQTTClientMbedOs.h>
#include <EthernetInterface.h>
#include <stdio.h>
#include <string.h>
#include "Sensor.h"

#include <iostream>

using namespace std;

extern EthernetInterface net;

class MQTTPlantClient {

public:
  MQTTPlantClient();

  void Authenticate(string clientID = "nucleo01", string username = "nucleo", string password = "1234");
  void Publish(const char* topic = "chilli", float telemetryType = -1, float telemetryValue = -1); //parameters: //string topic = "chilli/light", string telemetryType, float telemetryValue
  //void SendTelemetry(string topic, float value);

  //Getters & setters
  bool GetIsConnected();
  void SetIsConnected(bool isConnectedIn, string address = "192.168.1.6", uint16_t port = 1883);

protected:
  bool Connect(string address, uint16_t port);
  void Disconnect();

private:
    EthernetInterface net;
    TCPSocket socket;
    MQTTClient client;
    MQTTPacket_connectData connectionData;
    SocketAddress a;
    bool isConnected;
};
