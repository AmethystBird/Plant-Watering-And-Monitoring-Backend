/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "AnalogIn.h"
#include "NetworkData.h"
#include "dht20.h"
using namespace std;

// Blinking rate in milliseconds
//#define BLINKING_RATE     500ms

// AnalogIn light(A0);
DHT20 temperatureAndHumiditySensor;

vector<Sensor<AnalogIn>> updatingValuesFromAnalogSensors;

int main() {
  /*DHT20 th;
  while (true) {
    DHT20::EnvData dat = th.readTemperatureAndHumidity();
    printf("Temp: %f\n\rHumidity: %f\n\r", dat.temperature, dat.Humidity);
    wait_us(1000000);
  }

  int success = InitialiseAzureDemo();

  if (success != 0) {
    return success;
  }*/

  Timer provisionalTimer;

  Sensor<AnalogIn> lightSensor(A0, "Light", 500ms);
  //Sensor<DHT20> temperatureSensor(temperatureAndHumiditySensor, "Temperature", 500ms);
  //Sensor<DHT20> humiditySensor(temperatureAndHumiditySensor, "Humidity", 500ms);
  //Sensor<AnalogIn> moistureSensor(A0, "Moisture", 500ms);

  /*Sensor<AnalogIn> *lightSensor = new Sensor(A0, "Light", 500ms);
  Sensor<AnalogIn> *temperatureSensor = new Sensor("Temperature", 500ms);
  Sensor<AnalogIn> *humiditySensor = new Sensor("Humidity", 500ms);
  Sensor<AnalogIn> *moistureSensor = new Sensor(A3, "Moisture", 500ms);*/

  /*lightSensor->StartSensing();
  temperatureSensor->StartSensing();
  humiditySensor->StartSensing();
  moistureSensor->StartSensing();*/

  //vector<Sensor<AnalogIn>> updatingValuesFromAnalogSensors;
  //vector<Sensor<DHT20>*> updatingValuesFromDHT20Sensors;

  updatingValuesFromAnalogSensors.push_back(lightSensor);
  //updatingValuesFromSensors.push_back(temperatureSensor);
  //updatingValuesFromSensors.push_back(humiditySensor);
  //updatingValuesFromAnalogSensors->push_back(moistureSensor);

  NetworkData *networkData = new NetworkData(&updatingValuesFromAnalogSensors, 60000ms); // 60,000ms = 1m

  provisionalTimer.start();
  ThisThread::sleep_for(15000ms);
  while (provisionalTimer.elapsed_time() < 16s);
  lightSensor.StopSensing();
  //temperatureSensor.StopSensing();
  //humiditySensor.StopSensing();
  //moistureSensor.StopSensing();

  // Initialise the digital pin LED1 as an output
  /*DigitalOut led(LED1);

  while (true) {
      led = !led;
      //cout << light << endl;
      ThisThread::sleep_for(BLINKING_RATE);
  }*/
}