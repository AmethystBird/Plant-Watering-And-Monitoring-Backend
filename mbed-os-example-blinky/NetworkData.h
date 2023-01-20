#include "Azure.h"
#include "Sensor.h"

class NetworkData {
public:
NetworkData(vector<Sensor*> updatingValuesFromSensorsIn);
protected:
void UpdateLoop();
private:
Thread updateLoopThread;
bool isSending;
vector<Sensor*> updatingValuesFromSensors;
};