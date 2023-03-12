#pragma once
#include "publisher.h"

class NetworkData {
public:
  NetworkData(vector<Sensor *> *updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn);

  void StopSending();

private:
  Thread uploadLoopThread;
  bool isUploading;
  vector<Sensor *> *updatingValuesFromSensors;
  chrono::milliseconds readRate;
  EventQueue uploadQueue;
  Publisher* sensorDataPublisher;
};