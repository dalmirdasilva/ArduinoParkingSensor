#ifndef __ARDUINO_PARKING_SENSOR_SENSOR_H__
#define __ARDUINO_PARKING_SENSOR_SENSOR_H__ 1

#include <DistanceSensor.h>

class Sensor {

public:

  enum SensorState {
    ABSENT = 0x00,
    PRESENT = 0x01
  };

  enum SensorEvent {
    BECOME_ABSENT = 0x00,
    BECOME_PRESENT = 0x01
  };

  float threshold;
  float lastDistance;
  DistanceSensor *sensor;
  SensorState currentState;

public:

  Sensor(DistanceSensor *sensor, float threshold);

  bool hasTransitioned();

  unsigned char getState();
};

#endif /* __ARDUINO_PARKING_SENSOR_SENSOR_H__ */