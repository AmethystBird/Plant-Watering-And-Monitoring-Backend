#include "Sensor.h"
#include "dht20.h"
class DHT20Sensor : public Sensor {
public:
    DHT20Sensor(DHT20 sensorInterfaceIn, string valueTypeIn, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;

    virtual const char* GetTopic() override;
    virtual void SetTopic(const char* topicIn) override;

    const char* GetTopic2();
    void SetTopic2(const char* topic2In);

protected:
    void DisplaySensorValue();
    
    DHT20::EnvData sensorInterfaceType;

    const char* topic2;
};