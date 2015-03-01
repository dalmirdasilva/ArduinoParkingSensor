/**
 * Arduino - Parking Sensor
 *
 * StateTransitionNotifier.h
 *
 * Class responsible for take care state transition notification and listeners.
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__
#define __ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__ 1

#include <Settings.h>
#include "StateTransitionListener.h"
#include "Settings.h"

class StateTransitionNotifier {

  /**
   * Matrix holding the list of listeners on its respective 2D states transitions.
   */
  static StateTransitionListener *listeners[MAX_STATES][MAX_STATES][MAX_LISTENERS];

public:

  /**
   * Public constructor.
   */
  StateTransitionNotifier();

  /**
   * Adds an StateTransitionListener.
   *
   * @param fromState       The previous state which the listener will be notified.
   * @param toState         The next state which the listener will be notified.
   * @param listener        The listener.
   */
  void addStateTransitionListener(unsigned char fromState, unsigned char toState, StateTransitionListener *listener);

  /**
   * Notifies a state transition.
   *
   * @param fromState       The previous state which the listener will be notified.
   * @param toState         The next state which the listener will be notified.
   */
  void notifyStateTransition(unsigned char fromState, unsigned char toState);
};

#endif /* ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__ */