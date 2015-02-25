
#include <ArduinoParkingSensor.h>
#include <stdio.h>
#include <unistd.h>

void ArduinoParkingSensor::start() {
  while (1) {
    usleep(10000);
    printf("p");
    fflush(stdout);
  }
}