
#include <SensorManager.h>
#include <stdio.h>
#include <unistd.h>

SensorManager::SensorManager(Sensor **sensors, unsigned char *stateTable) :
    TransitionNotifier(), stateTable(stateTable), sensors(sensors) {
}

void SensorManager::start() {
  unsigned char i;
  Sensor *sensor;
  while (true) {
    for (i = 0; i < MAX_SENSORS; i++) {
      sensor = sensors[i];
      printf("%x\n", sensor->hasTransitioned());
    }
    usleep(10000);
    fflush(stdout);
  }
}