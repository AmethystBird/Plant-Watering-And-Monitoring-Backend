/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once
#include "NetworkData.h"
#include "dht20.h"
#include "AnalogSensor.h"
#include "DHT20Sensor.h"

//#include "DHT20Sensor.h"

using namespace std;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms

// AnalogIn light(A0);
DHT20 DHT20SensorLib;
//DHT20::EnvData dat;

vector<Sensor*> updatingValuesFromSensors;
NetworkData* networkData;

AnalogSensor* lightSensor = new AnalogSensor(A0, "Light", "chilli/light", 500ms);
AnalogSensor* moistureSensor = new AnalogSensor(A0, "Moisture", "chilli/moisture", 500ms);
DHT20Sensor* temperatureSensor = new DHT20Sensor("Temperature", "chilli/temperature", 500ms);

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

  // Initialise the digital pin LED1 as an output
  /*DigitalOut led(LED1);

  while (true) {
      led = !led;
      cout << "test cout" << endl;
      ThisThread::sleep_for(BLINKING_RATE);
  }*/

  //Timer provisionalTimer;

  //AnalogSensor* lightSensor = new AnalogSensor(A0, "Light", 500ms);

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

  //updatingValuesFromSensors.push_back(temperatureSensor);
  //updatingValuesFromSensors.push_back(humiditySensor);
  //updatingValuesFromAnalogSensors->push_back(moistureSensor);

//Work on this
  updatingValuesFromSensors.push_back((Sensor*)lightSensor);
  updatingValuesFromSensors.push_back((Sensor*)moistureSensor);
  updatingValuesFromSensors.push_back((Sensor*)temperatureSensor);

  string clientID = "nucleo01";
  string username = "nucleo";
  string password = "1234";

  networkData = new NetworkData(&updatingValuesFromSensors, 6000ms, clientID, username, password); // 60,000ms = 1m

  /*MQTTPlantClient client;
  client.Connect();
  client.Authenticate();

  client.Publish();
  cout << "Published default";
  wait_us(5000000); // 5s
  client.Publish("chilli/light", 4, 8);
  cout << "Published custom";

  wait_us(10000000); // 10s

  if (client.GetIsConnected()) {
    cout << "Client still connected; now disconnecting.";
  }
  client.Disconnect();
  if (!client.GetIsConnected()) {
    cout << "Client successfully disconnected.";
  }*/
  
  while (true) {
      ThisThread::sleep_for(1000ms);
  }
  /*provisionalTimer.start();
  ThisThread::sleep_for(15000ms);
  while (provisionalTimer.elapsed_time() < 16s);
  lightSensor->StopSensing();
  networkData->StopSending();*/

  //temperatureSensor.StopSensing();
  //humiditySensor.StopSensing();
  //moistureSensor.StopSensing();
}