
#include <stdio.h>
#include <unistd.h>
#include "StateMachine.h"

StateMachine::StateMachine(Sensor **sensors, unsigned char *stateTable, unsigned char initialState) :
    StateTransitionNotifier(), stateTable(stateTable), sensors(sensors) {
  state = initialState;
}

void StateMachine::start() {
  unsigned char i, sensorEvent, sensorState;
  Sensor *sensor;
  unsigned char nextState;
  bool sunIsShining = true;
  while (sunIsShining) {
    for (i = 0; i < MAX_SENSORS; i++) {
      sensor = sensors[i];
      if (sensor->hasTransitioned()) {
        sensorState = sensor->getState();
        sensorEvent = (sensorState == Sensor::ABSENT) ? Sensor::LEAVE : Sensor::ARRIVE;
        nextState = computeNextState(i, sensorEvent);
        if (nextState != UNDEFINED && state != nextState) {
          notifyStateTransition(state, nextState);
          state = nextState;
        }
      }
      fflush(stdout);
    }
    usleep(10000);
  }
}

unsigned char StateMachine::computeNextState(unsigned char sensorIndex, unsigned char sensorEvent) {
  unsigned int offset = (sensorIndex * MAX_EVENTS * MAX_STATES) + (sensorEvent * MAX_STATES) + state;
  return *(stateTable + offset);
}