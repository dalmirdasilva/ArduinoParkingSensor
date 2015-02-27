#include <Sensor.h>

Sensor::Sensor(DistanceSensor *sensor, float threshold) : threshold(threshold), sensor(sensor) {
  lastDistance = 0.0;
  currentState = ABSENT;
}

bool Sensor::hasTransitioned() {
  float distance;
  bool has;
  SensorState state;
  distance = sensor->getDistance();
  state = (distance > threshold) ? ABSENT : PRESENT;
  has = currentState != state;
  lastDistance = distance;
  currentState = state;
  return has;
}

unsigned char Sensor::getState() {
  return (unsigned char) currentState;
}
