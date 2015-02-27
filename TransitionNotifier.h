#ifndef __ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__
#define __ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__ 1

#include <TransitionListener.h>
#include <Settings.h>

class TransitionNotifier {
    
  static TransitionListener *listeners[MAX_STATES][MAX_STATES][MAX_LISTENERS];

public:

  TransitionNotifier();

  void addTransitionListener(unsigned char fromState, unsigned char toState, TransitionListener *listener);

  void notify(unsigned char fromState, unsigned char toState);
};

#endif /* ARDUINO_PARKING_SENSOR_TRANSITION_NOTIFIER__ */