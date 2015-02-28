#ifndef __ARDUINO_PARKING_SENSOR_SENSOR_H__
#define __ARDUINO_PARKING_SENSOR_SENSOR_H__ 1

#include "UltrasoundDistanceSensor.h"

class Sensor {

public:

  enum State {
    ABSENT = 0x00,
    PRESENT = 0x01
  };

  enum SensorEvent {
    PASS_BY = 0x00,
    TURN_UP = 0x01
  };

  float threshold;
  float minDistance;
  UltrasoundDistanceSensor *sensor;
  State currentState;

public:

  Sensor(UltrasoundDistanceSensor *sensor, float threshold, float minDistance);

  bool hasTransitioned();

  unsigned char getState();
};

#endif /* __ARDUINO_PARKING_SENSOR_SENSOR_H__ */