#include <stdio.h>
#include "Sensor.h"

Sensor::Sensor(UltrasoundDistanceSensor *sensor, float threshold, float maxDistance) :
        sensor(sensor), threshold(threshold), minDistance(minDistance) {
  currentState = ABSENT;
}

bool Sensor::hasTransitioned() {
  float distance;
  bool has = false;
  State state;
  printf("%p\n", sensor);
  distance = sensor->getDistance();
    state = ((distance ) > threshold) ? ABSENT : PRESENT;
    has = currentState != state;
    currentState = state;
  return has;
}

unsigned char Sensor::getState() {
  return (unsigned char) currentState;
}
