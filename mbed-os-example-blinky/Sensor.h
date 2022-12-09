#include "mbed.h"
#include <chrono>
#include <iostream>

class Sensor {
public:
Sensor(PinName sensorPinIn, string sensorTypeIn, chrono::milliseconds readRateIn);

AnalogIn GetSensor();

void StartSensing();
void StopSensing();

protected:
void DisplaySensorValue();
void UpdateLoop();

private:
Thread updateLoopThread;
AnalogIn sensor; //sensor
double sensorValue;
string sensorType;
chrono::milliseconds readRate;

bool isSensing;
};