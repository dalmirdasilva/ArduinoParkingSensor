
#include <SensorManager.h>
#include <stdio.h>
#include <unistd.h>

SensorManager::SensorManager(Sensor **sensors, unsigned char *stateTable, unsigned char initialState) :
    TransitionNotifier(), stateTable(stateTable), sensors(sensors) {
  currentState = initialState;
}

void SensorManager::start() {
  unsigned char i, sensorEvent, sensorState;
  Sensor *sensor;
  unsigned char nextState;
  while (true) {
    for (i = 0; i < MAX_SENSORS; i++) {
      sensor = sensors[i];
      if (sensor->hasTransitioned()) {
        sensorState = sensor->getState();
        sensorEvent = (sensorState == Sensor::ABSENT) ? Sensor::PASS_BY : Sensor::TURN_UP;
        nextState = computeNextState(i, sensorEvent);
        printf("currentState: %x -> nextState: %x\n", currentState, nextState);
        if (nextState != UNDEFINED && currentState != nextState) {
          printf("Notifying....\n");
          notifyTransition(currentState, nextState);
        }
      }
    }
    usleep(10000);
    fflush(stdout);
  }
}

unsigned char SensorManager::computeNextState(unsigned char sensorIndex, unsigned char sensorEvent) {
  return *(stateTable + (sensorIndex * sensorEvent + currentState));
}