#include "mbed.h"
#include <chrono>
#include <iostream>

class Sensor {
public:
Sensor(PinName sensorPinIn, string sensorTypeIn, chrono::milliseconds readRateIn);

AnalogIn GetSensor();

double StartSensing();

protected:
void DisplaySensorValue(string sensorLevelText);

private:
AnalogIn sensor; //sensor
double sensorValue;
string sensorType;
chrono::milliseconds readRate;
};