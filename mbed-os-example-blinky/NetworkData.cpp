#include "NetworkData.h"

NetworkData::NetworkData(vector<Sensor<AnalogIn>>* updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn)
{
    isUploading = true;
    updatingValuesFromSensors = updatingValuesFromSensorsIn;

    //uploadLoopThread.start(callback(this, &NetworkData::Update));

    auto DataUpload = [this, updatingValuesFromSensorsIn]() {
        NetworkDataUpdateLoop(updatingValuesFromSensorsIn);
    };

    auto DispatchToQueue = [this]() {
        this->uploadQueue.dispatch_forever();
    };

    uploadLoopThread.start(DispatchToQueue);
    uploadQueue.call_every(readRate, DataUpload);
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