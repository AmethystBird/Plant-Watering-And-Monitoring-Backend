#include "Sensor.h"
class AnalogSensor : public Sensor {
public:
    AnalogSensor(AnalogIn sensorInterfaceIn, string valueTypeIn, const char* topicIn, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;

  protected:
    void DisplaySensorValue();

    AnalogIn sensorInterfaceType;
};