#ifndef __ARDUINO_PARKING_SENSOR_SENSOR_MANAGER_H__
#define __ARDUINO_PARKING_SENSOR_SENSOR_MANAGER_H__ 1

#include <TransitionNotifier.h>
#include <Sensor.h>
#include <Settings.h>

class SensorManager : public TransitionNotifier {

  unsigned char *stateTable;
  Sensor **sensors;

public:

  SensorManager(Sensor **sensors, unsigned char *stateTable);

  void start();
};

#endif /* __ARDUINO_PARKING_SENSOR_SENSOR_MANAGER_H__  */