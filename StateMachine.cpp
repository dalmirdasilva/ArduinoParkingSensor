
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
  while (true) {
    for (i = 0; i < MAX_SENSORS; i++) {
      sensor = sensors[i];
      if (sensor->hasTransitioned()) {
        sensorState = sensor->getState();
        sensorEvent = (sensorState == Sensor::ABSENT) ? Sensor::PASS_BY : Sensor::TURN_UP;
        nextState = computeNextState(i, sensorEvent);
        printf("state: %x -> nextState: %x\n", state, nextState);
        if (nextState != UNDEFINED && state != nextState) {
          printf("Notifying....\n");
          notifyStateTransition(state, nextState);
        }
      }
    }
    usleep(10000);
    fflush(stdout);
  }
}

unsigned char StateMachine::computeNextState(unsigned char sensorIndex, unsigned char sensorEvent) {
  return *(stateTable + (sensorIndex * sensorEvent + state));
}