#pragma once
#include "Azure.h"

class NetworkData {
public:
  NetworkData(vector<Sensor<AnalogIn*>> updatingValuesFromSensorsIn,
              chrono::milliseconds uploadRateIn);

private:
  Thread uploadLoopThread;
  bool isUploading;
  vector<Sensor<AnalogIn*>> updatingValuesFromSensors;
  chrono::milliseconds readRate;
  EventQueue uploadQueue;
};