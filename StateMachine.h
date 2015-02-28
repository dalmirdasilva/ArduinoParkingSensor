#ifndef __ARDUINO_PARKING_SENSOR_STATE_MACHINE_H__
#define __ARDUINO_PARKING_SENSOR_STATE_MACHINE_H__ 1


#include "StateTransitionNotifier.h"
#include "Sensor.h"

class StateMachine : public StateTransitionNotifier {

  unsigned char *stateTable;
  Sensor **sensors;
  unsigned char state;

public:

  enum State {
    IDLE = 0x00,
    ARRIVE0 = 0x01,
    ARRIVE1 = 0x02,
    ARRIVE2 = 0x04,
    LEAVE0 = 0x08,
    LEAVE1 = 0x10,
    LEAVE2 = 0x20,
    UNDEFINED = 0xff
  };

  StateMachine(Sensor **sensors, unsigned char *stateTable, unsigned char initialState);

  unsigned char computeNextState(unsigned char sensorIndex, unsigned char sensorEvent);

  void start();
};

#endif /* __ARDUINO_PARKING_SENSOR_STATE_MACHINE_H__  */