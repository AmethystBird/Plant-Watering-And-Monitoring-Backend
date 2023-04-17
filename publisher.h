#include <MQTTClientMbedOs.h>
#include "Sensor.h"
#include "EthernetInterface.h"

class Publisher {
public:
  Publisher();
  void Connect(const char* address, uint16_t port, string* clientID, string* username, string* password);
  void Disconnect();
  void SendTelemetry(float value, float type);

bool isConnected;

private:
//NetworkInterface *net;
EthernetInterface net;
TCPSocket socket;
MQTTClient client;
MQTTPacket_connectData connectionData;
};