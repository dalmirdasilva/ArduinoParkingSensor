#include "Sensor.h"

Sensor::Sensor(DistanceSensor *sensor, float threshold, float minDistance, float maxDistance) :
    sensor(sensor), threshold(threshold), minDistance(minDistance), maxDistance(maxDistance) {
  currentState = ABSENT;
}

bool Sensor::hasTransitioned() {
  float distance;
  State state;
  distance = sensor->getDistance();
  if (distance >= minDistance && distance <= maxDistance) {
    state = ((distance - minDistance) > threshold) ? ABSENT : PRESENT;
    if (currentState != state) {
      currentState = state;
      return true;
    }
  }
  return false;
}

unsigned char Sensor::getState() {
  return (unsigned char) currentState;
}
