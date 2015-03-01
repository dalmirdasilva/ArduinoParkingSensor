/**
 * Arduino - Parking Sensor
 *
 * Sensor.h
 *
 * The sensor implementation. Real sensor driver is underling this class.
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_PARKING_SENSOR_SENSOR_H__
#define __ARDUINO_PARKING_SENSOR_SENSOR_H__ 1

#include "DistanceSensor.h"

class Sensor {

public:

  /**
   * Sensor state.
   * ABSENT means the sensor is not identifying any obstacle between the minimum and maximum distances.
   * PRESENT means there is an obstacle between the minimum and maximum distances.
   */
  enum State {
    ABSENT = 0x00,
    PRESENT = 0x01
  };

  /**
   * Sensor event.
   * Every time a sensor transitioned its state, an event was happened. If it was transitioned and the current state
   * is ABSENT the event will be LEAVE, if the current state is PRESENT, the event is ARRIVE.
   */
  enum Event {
    LEAVE = 0x00,
    ARRIVE = 0x01
  };

  /**
   * Underling sensor driver.
   */
  DistanceSensor *sensor;

  /**
   * Threshold is the limit between the minimum and maximum distances which is used to consider the sensor state.
   */
  float threshold;

  /**
   * Minimum distance is the low limit distance where the sensor will consider for measurement.
   */
  float minDistance;

  /**
   * Minimum distance is the high limit distance where the sensor will consider for measurement.
   */
  float maxDistance;

  /**
   * Machine state
   */
  State currentState;

public:

  /**
   * Public constructor.
   *
   * @param sensor        The underling sensor driver.
   * @param threshold     @see threshold above.
   * @param minDistance   @see minDistance above.
   * @param maxDistance   @see maxDistance above.
   */
  Sensor(DistanceSensor *sensor, float threshold, float minDistance, float maxDistance);

  /**
   * Reads the sensor and determine if the state has changed or not. Also sets the new state.
   *
   * @return  bool        If or not the state was transitioned.
   */
  bool hasTransitioned();

  /**
   * Current state.
   */
  unsigned char getState();
};

#endif /* __ARDUINO_PARKING_SENSOR_SENSOR_H__ */