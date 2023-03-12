#include <mosquitto.h>
#include "Sensor.h"

class Publisher {
public:
  Publisher();
  int Connect();
  void Disconnect();
  void SendTelemetry();

private:
struct mosquitto* payload;
};