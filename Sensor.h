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
    PASS_BY = 0x00,
    TURN_UP = 0x01
  };

  float minDistance;
  float maxDistance;
  float threshold;
  float lastDistance;
  DistanceSensor *sensor;
  SensorState currentState;

public:

  Sensor(DistanceSensor *sensor, float minDistance, float maxDistance, float threshold);

  bool hasTransitioned();

  unsigned char getState();
};

#endif /* __ARDUINO_PARKING_SENSOR_SENSOR_H__ */