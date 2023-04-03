#include <MQTTClientMbedOs.h>
#include "Sensor.h"

class Publisher {
public:
  Publisher();
  void Connect(const char* address, uint16_t port);
  void Disconnect();
  void SendTelemetry(float value, float type);

private:
NetworkInterface *net;
TCPSocket socket;
MQTTClient client;
MQTTPacket_connectData connectionData;
};