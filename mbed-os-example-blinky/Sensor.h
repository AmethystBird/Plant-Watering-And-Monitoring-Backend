#include "mbed.h"
//#include <chrono>
#include <iostream>
#include <vector>

class Sensor {
public:
Sensor(PinName sensorPinIn, string sensorTypeIn, chrono::milliseconds readRateIn);

AnalogIn GetSensor();

void StartSensing();
void StopSensing();

//float* GetUpdatingValues();
vector<float>* GetUpdatingValues();
float GetLastValue();

string GetSensorType();

protected:
void DisplaySensorValue();
float GetMockedSensorValue();
void UpdateLoop();

private:
Thread updateLoopThread;
AnalogIn sensorInput; //sensor
double sensorValue;
string sensorType;
chrono::milliseconds readRate;

bool isSensing;

vector<float> sensorBuffer;
};