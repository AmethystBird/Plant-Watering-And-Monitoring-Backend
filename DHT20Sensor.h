#include "Sensor.h"
#include "dht20.h"
class DHT20Sensor : public Sensor {
public:
    DHT20Sensor(string valueTypeIn, const char* topicIn, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;

protected:
  //Acquires last sensor value, sends it to the sensor buffer & prints it
  virtual void AcquireSensorValue() override;

  DHT20 DHT20SensorLib;
  DHT20::EnvData sensorInterfaceType;

  const char *topic2;
};