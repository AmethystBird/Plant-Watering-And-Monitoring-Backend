#pragma once
#include "Azure.h"

class NetworkData {
public:
  NetworkData(vector<Sensor*>* updatingValuesFromSensorsIn,
              chrono::milliseconds uploadRateIn);

private:
  Thread uploadLoopThread;
  bool isUploading;
  vector<Sensor*>* updatingValuesFromSensors;
  chrono::milliseconds readRate;
  EventQueue uploadQueue;
};