#include "Sensor.h"
class AnalogSensor : public Sensor {
public:
    AnalogSensor(AnalogIn sensorInterfaceIn, string valueTypeIn, const char* topicIn, chrono::milliseconds readRateIn);

    virtual float GetLastValue() override;

  protected:
    //Acquires last sensor value, sends it to the sensor buffer & prints it
    virtual void AcquireSensorValue() override;

    AnalogIn sensorInterfaceType;
};