/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "AnalogSensor.h"
#include "DHT20Sensor.h"
#include "NetworkData.h"
#include "dht20.h"

using namespace std;

vector<Sensor*> updatingValuesFromSensors;
NetworkData* networkData;

AnalogSensor lightSensor(A0, "Light", "chilli/light", 500ms);
AnalogSensor moistureSensor(A1, "Moisture", "chilli/moisture", 500ms);
DHT20Sensor temperatureSensor("Temperature", "chilli/temperature", 500ms);

int main() {
  //Assigning sensors to vector
   updatingValuesFromSensors.push_back(&lightSensor);
   updatingValuesFromSensors.push_back(&moistureSensor);
   updatingValuesFromSensors.push_back(&temperatureSensor);

  //Authentication credentials
  string clientID = "nucleo01";
  string username = "nucleo";
  string password = "1234";

   networkData = new NetworkData(&updatingValuesFromSensors, 6000ms, clientID, username, password); //Connect & routinely send telemetry (60,000ms = 1m)

  while (true)
  {
    ThisThread::sleep_for(1000ms);
  }
}