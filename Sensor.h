#pragma once
#include "AnalogIn.h"
#include "EventQueue.h"
#include "Sensor.h"
#include "mbed.h"
//#include <chrono>
#include <iostream>
#include <vector>

/*template <class SensorValue_t = float>
class SensorClass {
    protected:
     string _name;
     SensorValue_t _last;

     virtual SensorValue_t getLastValue() = 0; //pvf 
    public:
    string GetSensorName() {
        return _name;
    }
};

template <class SensorValue_t = float>
class AnalogSensor : public SensorClass<float> {

    private: 
    AnalogIn _adc;

    public:
    AnalogSensor(PinName adcPin, string nam) : _adc(adcPin) {
        _name = nam;
    }
    virtual SensorValue_t getLastValue() override  {
        
    }

};*/

class Sensor {
public:
  //sensorPin GetSensor();

  //template <class sensorPin>
  //void StartSensing(AnalogIn sensorInterfaceType);

  // float* GetUpdatingValues();
  vector<float> *GetUpdatingValues();
  virtual float GetLastValue() = 0;

  string GetSensorName();

  void StopSensing();

protected:
  void DisplaySensorValue();
  float GetMockedSensorValue();
  // void UpdateLoop();

  Thread updateLoopThread;
  EventQueue sensorQueue;

  string valueType;
  chrono::milliseconds readRate;

  vector<float> sensorBuffer;
};