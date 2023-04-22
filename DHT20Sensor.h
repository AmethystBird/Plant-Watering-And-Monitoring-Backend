#include "Sensor.h"
#include "dht20.h"
class DHT20Sensor : public Sensor {
public:
    DHT20Sensor(string valueTypeIn, string topicIn, chrono::milliseconds readRateIn);


protected:
  //Acquires last sensor value, sends it to the sensor buffer & prints it
  virtual void AcquireSensorValue() override;

  DHT20 DHT20SensorLib;
  DHT20::EnvData sensorInterfaceType;
public:
  virtual SensorValueAndMetadata_t GetLastValue() override;
};