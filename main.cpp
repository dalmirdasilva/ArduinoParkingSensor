#include <ArduinoParkingSensor.h>
#include <TransitionListener.h>
#include <TransitionNotifier.h>

int main(int argc, char* argv[]) {

  enum States {
    IDLE = 0x00,
    E0 = 0x01,
    E1 = 0x02
  };

  enum Events {

    ON_FINISH_ENTRY = 0x02,
    ON_FINISH_EXIT = 0x04
  };

  ArduinoParkingSensor sensor;
  sensor.start();

  return 0;
}
