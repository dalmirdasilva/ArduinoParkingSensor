#include "StateMachine.h"
#include <Arduino.h>

StateMachine::StateMachine(Sensor **sensors, unsigned char *stateTable, unsigned char initialState) :
    StateTransitionNotifier(), stateTable(stateTable), sensors(sensors) {
  state = initialState;
}

void StateMachine::start() {
  Sensor *sensor;
  unsigned char i, sensorState, nextState;
  bool isSunShining = true;
  while (isSunShining) {
    delay(MIN_SOUND_DISSIPATION_TIME_MILLIS);
    for (i = 0; i < MAX_SENSORS; i++) {
        sensor = sensors[i];
      if (sensor->hasTransitioned()) {
        sensorState = sensor->getState();
        nextState = computeNextState(i, sensorState);
        if (nextState != UNDEFINED && state != nextState) {
          notifyStateTransition(state, nextState);
          state = nextState;
        }
      }
    }
  }
}

unsigned char StateMachine::computeNextState(unsigned char sensorIndex, unsigned char sensorState) {
  unsigned int offset = (sensorIndex * MAX_EVENTS_TIMES_MAX_STATES) + (sensorState * MAX_STATES) + state;
  return *(stateTable + offset);
}
