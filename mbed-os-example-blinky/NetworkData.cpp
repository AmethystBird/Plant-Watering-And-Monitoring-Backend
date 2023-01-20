#include "NetworkData.h"

NetworkData::NetworkData(vector<Sensor*> updatingValuesFromSensorsIn)
{
    isSending = false;
    updatingValuesFromSensors = updatingValuesFromSensorsIn;

    updateLoopThread.start(callback(this, &NetworkData::UpdateLoop));
}

void NetworkData::UpdateLoop() {
    bool trace_on = MBED_CONF_APP_IOTHUB_CLIENT_TRACE;
    tickcounter_ms_t interval = 100;
    IOTHUB_CLIENT_RESULT res;

    LogInfo("Initializing IoT Hub client");
    IoTHub_Init();



    IOTHUB_DEVICE_CLIENT_HANDLE client_handle = IoTHubDeviceClient_CreateFromConnectionString(
        azure_cloud::credentials::iothub_connection_string,
        MQTT_Protocol
    );
    if (client_handle == nullptr) {
        LogError("Failed to create IoT Hub client handle");
        goto cleanup;
    }

    // Enable SDK tracing
    res = IoTHubDeviceClient_SetOption(client_handle, OPTION_LOG_TRACE, &trace_on);
    if (res != IOTHUB_CLIENT_OK) {
        LogError("Failed to enable IoT Hub client tracing, error: %d", res);
        goto cleanup;
    }

    // Enable static CA Certificates defined in the SDK
    res = IoTHubDeviceClient_SetOption(client_handle, OPTION_TRUSTED_CERT, certificates);
    if (res != IOTHUB_CLIENT_OK) {
        LogError("Failed to set trusted certificates, error: %d", res);
        goto cleanup;
    }

    // Process communication every 100ms
    res = IoTHubDeviceClient_SetOption(client_handle, OPTION_DO_WORK_FREQUENCY_IN_MS, &interval);
    if (res != IOTHUB_CLIENT_OK) {
        LogError("Failed to set communication process frequency, error: %d", res);
        goto cleanup;
    }

    // set incoming message callback
    res = IoTHubDeviceClient_SetMessageCallback(client_handle, on_message_received, nullptr);
    if (res != IOTHUB_CLIENT_OK) {
        LogError("Failed to set message callback, error: %d", res);
        goto cleanup;
    }

    // Set incoming command callback
    res = IoTHubDeviceClient_SetDeviceMethodCallback(client_handle, on_method_callback, nullptr);
    if (res != IOTHUB_CLIENT_OK) {
        LogError("Failed to set method callback, error: %d", res);
        goto cleanup;
    }

    // Set connection/disconnection callback
    res = IoTHubDeviceClient_SetConnectionStatusCallback(client_handle, on_connection_status, nullptr);
    if (res != IOTHUB_CLIENT_OK) {
        LogError("Failed to set connection status callback, error: %d", res);
        goto cleanup;
    }

    // Send ten message to the cloud (one per second)
    // or until we receive a message from the cloud
    IOTHUB_MESSAGE_HANDLE message_handle;
    char message[83];
    for (int i = 0; i < 10; ++i) {
        if (message_received) {
            // If we have received a message from the cloud, don't send more messeges
            break;
        }
        //Send data in this format:
        /*
            {
                "LightLevel" : 0.12,
                "Temperature" : 36.0
            }

        */

        /*string messageToSend = "{ ";
        vector<float> values;
        for (int i = 0; updatingValuesFromSensors.size(); i++)
        {
            string valueType = updatingValuesFromSensors[i]->GetSensorType();
            messageToSend = messageToSend + "\"" + valueType + "\" : %5.2f, ";
        }
        messageToSend = messageToSend + "}";

        for (int i = 0; updatingValuesFromSensors.size(); i++)
        {
            float value = updatingValuesFromSensors[i]->GetLastValue();
            string valueToSend = std::to_string(value);
            messageToSend = messageToSend + valueToSend;
        }*/

        float lightValue = updatingValuesFromSensors[0]->GetLastValue();
        float temperatureValue = updatingValuesFromSensors[1]->GetLastValue();
        float humidityValue = updatingValuesFromSensors[2]->GetLastValue();
        float moistureValue = updatingValuesFromSensors[3]->GetLastValue();
        sprintf(message, "{ \"Light\" : %5.2f, \"Temperature\" : %5.2f, \"Humidity\" : %5.2f, \"Moisture\" : %5.2f }", lightValue, temperatureValue, humidityValue, moistureValue);

        /*double light = (float) i;
        double temp  = (float)36.0f-0.1*(float)i;
        sprintf(message, "{ \"LightLevel\" : %5.2f, \"Temperature\" : %5.2f }", light, temp);*/
        LogInfo("Sending: \"%s\"", message);

        message_handle = IoTHubMessage_CreateFromString(message);
        if (message_handle == nullptr) {
            LogError("Failed to create message");
            goto cleanup;
        }

        res = IoTHubDeviceClient_SendEventAsync(client_handle, message_handle, on_message_sent, nullptr);
        IoTHubMessage_Destroy(message_handle); // message already copied into the SDK

        if (res != IOTHUB_CLIENT_OK) {
            LogError("Failed to send message event, error: %d", res);
            goto cleanup;
        }

        ThisThread::sleep_for(60s);
    }

    // If the user didn't manage to send a cloud-to-device message earlier,
    // let's wait until we receive one
    while (!message_received) {
        // Continue to receive messages in the communication thread
        // which is internally created and maintained by the Azure SDK.
        sleep();
    }

cleanup:
    IoTHubDeviceClient_Destroy(client_handle);
    IoTHub_Deinit();
}