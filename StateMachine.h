/**
 * Arduino - Parking Sensor
 *
 * StateMachine.h
 *
 * State Machine class.
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_PARKING_SENSOR_STATE_MACHINE_H__
#define __ARDUINO_PARKING_SENSOR_STATE_MACHINE_H__ 1

#include "StateTransitionNotifier.h"
#include "Sensor.h"

class StateMachine : public StateTransitionNotifier {

  /**
   * State table.
   */
  unsigned char *stateTable;

  /**
   * Sensor list.
   */
  Sensor **sensors;

  /**
   * Current state.
   */
  unsigned char state;

public:

  /**
   * Possible states.
   */
  enum State {
    UNDEFINED = 0x00,
    IDLE = 0x01,
    ARRIVE0 = 0x02,
    ARRIVE1 = 0x03,
    ARRIVE2 = 0x04,
    LEAVE0 = 0x05,
    LEAVE1 = 0x06,
    LEAVE2 = 0x07
  };

  /**
   * Public constructor.
   */
  StateMachine(Sensor **sensors, unsigned char *stateTable, unsigned char initialState);

  /**
   * Computes the next state.
   */
  unsigned char computeNextState(unsigned char sensorIndex, unsigned char sensorEvent);

  /**
   * Infinite loop.
   */
  void start();
};

#endif /* __ARDUINO_PARKING_SENSOR_STATE_MACHINE_H__  */