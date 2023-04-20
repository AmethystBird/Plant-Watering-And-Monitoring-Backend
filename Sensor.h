#pragma once
#include "mbed.h"
#include "EventQueue.h"
#include "Sensor.h"
#include <iostream>
#include <vector>

class Sensor {
public:
  //Gets a vector of all sensor values; currently unused
  //vector<float> *GetUpdatingValues();
  //Gets the most recent sensor value
  virtual float GetLastValue() = 0;

  //Gets the sensor name / value type
  string GetSensorName();

  //Stops sensor sensing
  void StopSensing();

  //Gets the Mosquitto topic where telemetry is sent
  const char* GetTopic();
  //Sets the Mosquitto topic where telemetry is sent
  void SetTopic(const char* topicIn);

protected:
  //Acquires last sensor value, sends it to the sensor buffer & prints it
  virtual void AcquireSensorValue() = 0;

  //Generates & gets a random number for the sake of mocking sensor data
  float GetMockedSensorValue();

  Thread updateLoopThread;
  EventQueue sensorQueue;

  string valueType;
  chrono::milliseconds readRate;

  vector<float> sensorBuffer;
  float currentSensorValue;

  const char* topic;
};