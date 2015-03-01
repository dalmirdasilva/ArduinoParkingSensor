/**
 * Arduino - Parking Sensor
 *
 * StateTransitionListener.h
 *
 * Abstract class. All StateTransitionListeners would implement this class.
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_PARKING_SENSOR_TRANSITION_LISTENER__
#define __ARDUINO_PARKING_SENSOR_TRANSITION_LISTENER__ 1

class StateTransitionListener {
    
public:

  /**
   * Event received.
   */
  virtual void eventReceived(unsigned char fromState, unsigned char toState) = 0;
};

#endif /* __ARDUINO_PARKING_SENSOR_TRANSITION_LISTENER__ */