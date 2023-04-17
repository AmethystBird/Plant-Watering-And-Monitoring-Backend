#pragma once
#include "mbed.h"
#include "EventQueue.h"
#include "Sensor.h"
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

  virtual const char* GetTopic() = 0;
  virtual void SetTopic(const char* topicIn) = 0;

protected:
  void DisplaySensorValue();
  float GetMockedSensorValue();
  // void UpdateLoop();

  Thread updateLoopThread;
  EventQueue sensorQueue;

  string valueType;
  chrono::milliseconds readRate;

  vector<float> sensorBuffer;

  const char* topic;
};