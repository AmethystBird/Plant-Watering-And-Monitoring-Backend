#pragma once
#include "mbed.h"
#include "EventQueue.h"
//#include "Sensor.h"
#include <iostream>
#include <vector>
#include <array>
#include <queue>


typedef struct sensorValueAndMetadata {
    float sensorValue;
    string valueDateTime;
  } SensorValueAndMetadata_t;

class Sensor {
public:

  //Gets a vector of all sensor values; currently unused
  //vector<float> *GetUpdatingValues();
  //Gets the most recent sensor value

  //Gets the sensor name / value type
  string GetSensorName();

  //Stops sensor sensing
  void StopSensing();

  //Gets the Mosquitto topic where telemetry is sent
  string GetTopic();
  //Sets the Mosquitto topic where telemetry is sent
  void SetTopic(string topicIn);

  unsigned int GetSensorBufferSize();

//   struct sensorValueAndMetadata {
//     float sensorValue;
//     char* valueDateTime;
//   };
//vector<Sensor::sensorValueAndMetadata>
  virtual SensorValueAndMetadata_t GetLastValue() = 0;

  //static SensorValueAndMetadata_t GetRedundantData();

protected:
  //Acquires last sensor value, sends it to the sensor buffer & prints it
  virtual void AcquireSensorValue() = 0;

  //Generates & gets a random number for the sake of mocking sensor data
  float GetMockedSensorValue();

  Thread updateLoopThread;
  EventQueue sensorQueue;

  string valueType;
  chrono::milliseconds readRate;

  //vector<float> sensorBuffer;

  queue<sensorValueAndMetadata> sensorBuffer;

  float currentSensorValue;

  string topic;
};