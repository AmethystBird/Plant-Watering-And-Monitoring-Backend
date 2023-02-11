#include "Sensor.h"
#include "dht20.h"

class DHT20Sensor : public Sensor {
public:
    DHT20Sensor(DHT20 sensorInterfaceIn, string valueTypeIn, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;
protected:
    void DisplaySensorValue();
    
    DHT20::EnvData sensorInterfaceType;
};