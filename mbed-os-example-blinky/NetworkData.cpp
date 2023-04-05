#include "NetworkData.h"

NetworkData::NetworkData(vector<Sensor*>* updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn, string clientIDIn, string usernameIn, string passwordIn)
{
    isUploading = true;
    updatingValuesFromSensors = updatingValuesFromSensorsIn;
    clientID = clientIDIn;
    username = usernameIn;
    password = passwordIn;

    //uploadLoopThread.start(callback(this, &NetworkData::Update));

    auto DataUpload = [this, updatingValuesFromSensorsIn]() {
        //NetworkDataUpdateLoop(updatingValuesFromSensorsIn);
        //sensorDataPublisher->Connect("localhost", 1883);

        if (sensorDataPublisher->isConnected == false)
        {
            sensorDataPublisher->Connect("192.168.1.6", 1883, &clientID, &username, &password);
            
            sensorDataPublisher->SendTelemetry(32, 64);
        }
        else {
            sensorDataPublisher->SendTelemetry(32, 64);
        }

        //const char* address, uint16_t port, string* clientID, string* username, string* password
    };

    auto DispatchToQueue = [this]() {
        this->uploadQueue.dispatch_forever();
    };

    uploadLoopThread.start(DispatchToQueue);
    uploadQueue.call_every(readRate, DataUpload);
}

void NetworkData::StopSending()
{
    uploadQueue.break_dispatch();
}

//Called by thread as proxy to uploading values
/*void NetworkData::Update()
{
    while (isUploading)
    {
        NetworkDataUpdateLoop(updatingValuesFromSensors);
        ThisThread::sleep_for(readRate);
    }
    uploadLoopThread.join();
}*/