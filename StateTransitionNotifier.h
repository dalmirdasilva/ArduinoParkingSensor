#ifndef __ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__
#define __ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__ 1

#include <Settings.h>
#include "StateTransitionListener.h"
#include "Settings.h"

class StateTransitionNotifier {
    
  static StateTransitionListener *listeners[MAX_STATES][MAX_STATES][MAX_LISTENERS];

public:

  StateTransitionNotifier();

  void addStateTransitionListener(unsigned char fromState, unsigned char toState, StateTransitionListener *listener);

  void notifyStateTransition(unsigned char fromState, unsigned char toState);
};

#endif /* ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__ */