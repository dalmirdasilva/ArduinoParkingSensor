#include "StateMachine.h"
#include <Arduino.h>

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
    delay(MIN_SOUND_DISSIPATION_TIME_MILLIS);
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
    }
  }
}

unsigned char StateMachine::computeNextState(unsigned char sensorIndex, unsigned char sensorEvent) {
  unsigned int offset = (sensorIndex * MAX_EVENTS_TIMES_MAX_STATES) + (sensorEvent * MAX_STATES) + state;
  return *(stateTable + offset);
}
