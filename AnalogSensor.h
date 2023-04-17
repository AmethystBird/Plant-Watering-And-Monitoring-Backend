#include "Sensor.h"
class AnalogSensor : public Sensor {
public:
    AnalogSensor(AnalogIn sensorInterfaceIn, string valueType, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;

    virtual const char* GetTopic() override;
    virtual void SetTopic(const char* topicIn) override;

  protected:
    void DisplaySensorValue();

    AnalogIn sensorInterfaceType;
};