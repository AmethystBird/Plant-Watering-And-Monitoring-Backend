#include "NetworkData.h"

NetworkData::NetworkData(vector<Sensor*>* updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn)
{
    isUploading = true;
    updatingValuesFromSensors = updatingValuesFromSensorsIn;

    //uploadLoopThread.start(callback(this, &NetworkData::Update));

    auto DataUpload = [this, updatingValuesFromSensorsIn]() {
        //NetworkDataUpdateLoop(updatingValuesFromSensorsIn);
        sensorDataPublisher->Connect();
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