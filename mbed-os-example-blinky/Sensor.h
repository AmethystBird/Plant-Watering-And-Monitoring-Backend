#pragma once
#include "EventQueue.h"
#include "mbed.h"
#include "Sensor.h"
//#include <chrono>
#include <iostream>
#include <vector>

template <class sensorPin>
class Sensor {
public:
  Sensor(sensorPin sensorPinIn, string sensorNameIn,
         chrono::milliseconds readRateIn);

  AnalogIn GetSensor();

  // void StartSensing();
  void StopSensing();

  // float* GetUpdatingValues();
  vector<float> *GetUpdatingValues();
  float GetLastValue();

  string GetSensorType();

protected:
  void DisplaySensorValue();
  float GetMockedSensorValue();
  // void UpdateLoop();

private:
  Thread updateLoopThread;
  EventQueue sensorQueue;
  sensorPin sensorType; // sensor
  // double sensorValue;
  string sensorName;
  chrono::milliseconds readRate;

  bool isSensing;

  vector<float> sensorBuffer;
};