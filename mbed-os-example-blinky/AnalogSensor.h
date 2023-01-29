#include "Sensor.h"

class AnalogSensor : public Sensor {
public:
    AnalogSensor(AnalogIn sensorInterfaceIn, string valueType, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;

protected:
    AnalogIn sensorInterfaceType;
};