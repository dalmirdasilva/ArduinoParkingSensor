
#include <EventNotifier.h>

class ArduinoParkingSensor : public EventNotifier {

public:

  enum Events {
    ON_SENSOR_READ = 0x01,
    ON_FINISH_ENTRY = 0x02,
    ON_FINISH_EXIT = 0x04
  };

  void start();

};
