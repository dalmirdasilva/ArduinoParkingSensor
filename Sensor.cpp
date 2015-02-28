#include <stdio.h>
#include "Sensor.h"
#include "DistanceSensor.h"

Sensor::Sensor(DistanceSensor *sensor, float minDistance, float maxDistance, float threshold) :
    minDistance(minDistance), maxDistance(maxDistance), threshold(threshold), sensor(sensor) {
  lastDistance = 0.0;
  currentState = ABSENT;
}

bool Sensor::hasTransitioned() {
  float distance;
  bool has = false;
  State state;
  printf("%p\n", sensor);
  distance = sensor->getDistance();
  if (distance >= minDistance && distance <= maxDistance) {
    state = ((distance - minDistance) > threshold) ? ABSENT : PRESENT;
    has = currentState != state;
    lastDistance = distance;
    currentState = state;
  }
  return has;
}

unsigned char Sensor::getState() {
  return (unsigned char) currentState;
}
