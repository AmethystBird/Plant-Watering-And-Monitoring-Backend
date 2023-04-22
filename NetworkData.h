#pragma once
#include "MQTTPlantClient.h"

class NetworkData {
public:
  NetworkData(vector<Sensor *> *updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn, string clientIDIn, string usernameIn, string passwordIn);

  //Stops telemetry being sent
  void StopSending();

private:
  Thread uploadLoopThread;
  bool isUploading;
  vector<Sensor *> *updatingValuesFromSensors;
  chrono::milliseconds readRate;
  EventQueue uploadQueue;
  //Publisher* sensorDataPublisher;
  MQTTPlantClient sensorDataPublisher;

  string clientID;
  string username;
  string password;
};