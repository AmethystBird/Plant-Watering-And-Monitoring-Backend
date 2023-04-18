#include "NetworkData.h"
DigitalOut blue(LED2,1);

NetworkData::NetworkData(vector<Sensor*>* updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn, string clientIDIn, string usernameIn, string passwordIn)
{
    isUploading = true;
    updatingValuesFromSensors = updatingValuesFromSensorsIn;
    clientID = clientIDIn;
    username = usernameIn;
    password = passwordIn;
    
    auto DataUpload = [this]() {
        if (sensorDataPublisher.GetIsConnected() == false)
        {
            //blue = !blue;
            sensorDataPublisher.SetIsConnected(true);
            sensorDataPublisher.Authenticate();
            //blue = !blue;
        } else {
            cout << "NetworkData Constructor: GetIsConnected() returns true" << endl;
        }

        for (unsigned int i = 0; i < updatingValuesFromSensors->size(); i++)
        {
            Sensor* indexedSensor = updatingValuesFromSensors->at(i);
            sensorDataPublisher.Publish(indexedSensor->GetTopic(), 0.f, indexedSensor->GetLastValue());
        }
    };

    auto DispatchToQueue = [&]() {
        this->uploadQueue.dispatch_forever();
    };

    uploadLoopThread.start(DispatchToQueue);
    this->uploadQueue.call_every(10s, DataUpload);
}

void NetworkData::StopSending()
{
    uploadQueue.break_dispatch();
}