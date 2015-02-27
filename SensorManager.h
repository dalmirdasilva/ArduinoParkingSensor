#ifndef __ARDUINO_PARKING_SENSOR_SENSOR_MANAGER_H__
#define __ARDUINO_PARKING_SENSOR_SENSOR_MANAGER_H__ 1

#include <TransitionNotifier.h>
#include <Sensor.h>
#include <Settings.h>

class SensorManager : public TransitionNotifier {

  unsigned char *stateTable;
  Sensor **sensors;
  unsigned char currentState;

public:

  enum States {
    IDLE = 0x00,
    ARRIVE0 = 0x01,
    ARRIVE1 = 0x02,
    ARRIVE2 = 0x04,
    LEAVE0 = 0x08,
    LEAVE1 = 0x10,
    LEAVE2 = 0x20,
    UNDEFINED = 0xff
  };

  SensorManager(Sensor **sensors, unsigned char *stateTable);

  void start();
};

#endif /* __ARDUINO_PARKING_SENSOR_SENSOR_MANAGER_H__  */