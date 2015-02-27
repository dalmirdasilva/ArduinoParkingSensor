
#include <SensorManager.h>
#include <stdio.h>
#include <unistd.h>

SensorManager::SensorManager(Sensor **sensors, unsigned char *stateTable) :
    TransitionNotifier(), stateTable(stateTable), sensors(sensors) {
  currentState = IDLE;
}

void SensorManager::start() {
  unsigned char i, event, sensorState;
  Sensor *sensor;
  unsigned char nextState;
  while (true) {
    for (i = 0; i < MAX_SENSORS; i++) {
      sensor = sensors[i];
      if (sensor->hasTransitioned()) {
        sensorState = sensor->getState();
        event = (sensorState == Sensor::ABSENT) ? Sensor::BECOME_ABSENT : Sensor::BECOME_PRESENT;
        nextState = (unsigned char) (stateTable + (i * event + currentState));
        if (currentState != nextState)
          notify(currentState, nextState)
        }
      }
    }
    usleep(10000);
    fflush(stdout);
  }


}