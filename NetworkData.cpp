#include "NetworkData.h"
DigitalOut blue(LED2,1);

NetworkData::NetworkData(vector<Sensor*>* updatingValuesFromSensorsIn, chrono::milliseconds uploadRateIn, string clientIDIn, string usernameIn, string passwordIn)
{
    isUploading = true;
    updatingValuesFromSensors = updatingValuesFromSensorsIn;
    clientID = clientIDIn;
    username = usernameIn;
    password = passwordIn;

    //uploadLoopThread.start(callback(this, &NetworkData::Update));

    //auto DataUpload = [this, &updatingValuesFromSensorsIn]() {
    auto DataUpload = [this]() {
        //NetworkDataUpdateLoop(updatingValuesFromSensorsIn);
        //sensorDataPublisher->Connect("localhost", 1883);

        if (sensorDataPublisher.GetIsConnected() == false)
        {
            blue = !blue;
            //sensorDataPublisher->Connect("192.168.1.6", 1883, &clientID, &username, &password);    
            sensorDataPublisher.SetIsConnected(true);
            sensorDataPublisher.Authenticate();
            blue = !blue;
            //sensorDataPublisher->SendTelemetry(32, 64);
        } else {
            cout << "NetworkData Constructor: GetIsConnected() returns true" << endl;
        }
        sensorDataPublisher.Publish("chilli/light", 0.f, updatingValuesFromSensors->back()->GetLastValue());

        //const char* address, uint16_t port, string* clientID, string* username, string* password
    };

    auto DispatchToQueue = [&]() {
        this->uploadQueue.dispatch_forever();
    };

    uploadLoopThread.start(DispatchToQueue);
    this->uploadQueue.call_every(10s, DataUpload);
    //uploadQueue.call_every(readRate, DataUpload);
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