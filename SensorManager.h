#ifndef __ARDIONO_PARKING_SENSOR_SENSOR_MANAGER_H__
#define __ARDIONO_PARKING_SENSOR_SENSOR_MANAGER_H__ 1

#include <TransitionNotifier.h>
#include <Sensor.h>

#define MAX_SENSORS 4
#define MAX_EVENTS 2
#define MAX_SEMSOR_STATES 6

class SensorManager : public TransitionNotifier {

  unsigned char *stateTable;
  Sensor **sensors;

public:

  SensorManager(Sensor **sensors, unsigned char *stateTable);

  void start();
};

#endif /* __ARDIONO_PARKING_SENSOR_SENSOR_MANAGER_H__  */