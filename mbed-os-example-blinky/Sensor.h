#pragma once
#include "EventQueue.h"
#include "Sensor.h"
#include "mbed.h"
//#include <chrono>
#include <iostream>
#include <vector>

template <class sensorPin>
class Sensor {
public:
  Sensor(sensorPin sensorPinIn, string sensorNameIn,
         chrono::milliseconds readRateIn);

  //sensorPin GetSensor();

  //template <class sensorPin>
  void StartSensing(sensorPin sensorType);

  void StopSensing();

  // float* GetUpdatingValues();
  vector<float> *GetUpdatingValues();
  float GetLastValue();

  string GetSensorName();

protected:
  void DisplaySensorValue();
  float GetMockedSensorValue();
  // void UpdateLoop();

private:
  Thread updateLoopThread;
  EventQueue sensorQueue;

  sensorPin sensorType;

  //AnalogIn sensorType; // sensor
  // double sensorValue;
  string sensorName;
  chrono::milliseconds readRate;

  bool isSensing;

  vector<float> sensorBuffer;
};