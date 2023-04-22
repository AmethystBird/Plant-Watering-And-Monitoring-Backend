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

  //Authenticates user to Mosquitto server. Requires that a connection has already been established.
  void Authenticate(string clientID = "nucleo01", string username = "nucleo", string password = "1234");
  //Sends telemetry to Mosquitto server. Requires that connection & authentication have both been established.
  void Publish(string topic, float telemetryType, SensorValueAndMetadata_t telemetryData);
  //void Publish(string topic = "chilli", float telemetryType = -1, SensorValueAndMetadata_t telemetryData = Sensor::GetRedundantData());
  //void Publish(const char* topic = "chilli", float telemetryType = -1, float telemetryValue = -1);

  //Gets whether a connection to a given Mosquitto server has been established
  bool GetIsConnected();
  //Sets whether a connection to a given Mosquitto server has been established
  void SetIsConnected(bool isConnectedIn, string address = "192.168.1.6", uint16_t port = 1883);

protected:
  //Connects to a given Mosquitto server
  bool Connect(string address, uint16_t port);
  //Disconnects from a given Mosquitto server
  void Disconnect();

private:
    EthernetInterface net;
    TCPSocket socket;
    MQTTClient client;
    MQTTPacket_connectData connectionData;
    SocketAddress a;
    bool isConnected;
};
