#include "Sensor.h"
class AnalogSensor : public Sensor {

public:
    AnalogSensor(PinName sensorInterfaceIn_Pin, string valueTypeIn, string topicIn, chrono::milliseconds readRateIn);


protected:
    //Acquires last sensor value, sends it to the sensor buffer & prints it
    virtual void AcquireSensorValue() override;

    AnalogIn sensorInterfaceType;
public:
    virtual SensorValueAndMetadata_t GetLastValue() override;
};