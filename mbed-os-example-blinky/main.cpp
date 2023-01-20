/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "NetworkData.h"

using namespace std;

// Blinking rate in milliseconds
//#define BLINKING_RATE     500ms

//AnalogIn light(A0);

int main()
{
    /*DHT th(D14, DHT11);
    wait_us(1000000);
    int err = th.readData();
    wait_us(1000000);
    err = th.readData();
    if (err != 0) {
        puts("Error from sensor");
        printf("%d\n\r", err);
        //while(1);
    }

    float temp = th.ReadTemperature(CELCIUS);
    printf("Temp: %f\n\r", temp);

    while(1);*/

    /*int success = InitialiseAzureDemo();

    if (success != 0)
    {
        return success;
    }*/

    Timer provisionalTimer;

    Sensor* lightSensor = new Sensor(A0, "Light", 500ms);
    Sensor* temperatureSensor = new Sensor(A3, "Temperature", 500ms);
    Sensor* humiditySensor = new Sensor(A3, "Humidity", 500ms);
    Sensor* moistureSensor = new Sensor(A3, "Moisture", 500ms);

    lightSensor->StartSensing();
    temperatureSensor->StartSensing();
    humiditySensor->StartSensing();
    moistureSensor->StartSensing();

    vector<Sensor*> updatingValuesFromSensors;

    updatingValuesFromSensors.push_back(lightSensor);
    updatingValuesFromSensors.push_back(temperatureSensor);
    updatingValuesFromSensors.push_back(humiditySensor);
    updatingValuesFromSensors.push_back(moistureSensor);

    //NetworkData* networkData = new NetworkData(updatingValuesFromSensors);
    //networkData->SendData();

    provisionalTimer.start();
    ThisThread::sleep_for(15000ms);
    while (provisionalTimer.elapsed_time() < 5s);
    lightSensor->StopSensing();
    temperatureSensor->StopSensing();
    humiditySensor->StopSensing();
    moistureSensor->StopSensing();

    // Initialise the digital pin LED1 as an output
    /*DigitalOut led(LED1);

    while (true) {
        led = !led;
        //cout << light << endl;
        ThisThread::sleep_for(BLINKING_RATE);
    }*/
}