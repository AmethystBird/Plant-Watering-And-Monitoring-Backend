/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <iostream>
#include "Sensor.h"

using namespace std;

// Blinking rate in milliseconds
//#define BLINKING_RATE     500ms

//AnalogIn light(A0);

int main()
{
    Timer provisionalTimer;

    Sensor* lightSensor = new Sensor(A0, "light", 500ms);
    lightSensor->StartSensing();
    provisionalTimer.start();
    ThisThread::sleep_for(15000ms);
    //while (provisionalTimer.elapsed_time() < 5s);
    lightSensor->StopSensing();

    // Initialise the digital pin LED1 as an output
    /*DigitalOut led(LED1);

    while (true) {
        led = !led;
        //cout << light << endl;
        ThisThread::sleep_for(BLINKING_RATE);
    }*/
}
