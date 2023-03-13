#include <MQTTClientMbedOs.h>
#include "Sensor.h"

class Publisher {
public:
  Publisher();
  int Connect(const char* address, uint16_t port);
  void Disconnect();
  void SendTelemetry();

private:
NetworkInterface *net;
TCPSocket socket;
};