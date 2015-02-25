#include <ArduinoParkingSensor.h>
#include <EventListener.h>
#include <EventNotifier.h>

int main(int argc, char* argv[]) {

  ArduinoParkingSensor sensor;
  sensor.start();

  return 0;
}
