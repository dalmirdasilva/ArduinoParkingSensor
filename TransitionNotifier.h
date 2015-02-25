#ifndef __ARDIONO_PARKING_SENSOR_TRANSITION_NOTIFIER__
#define __ARDIONO_PARKING_SENSOR_TRANSITION_NOTIFIER__ 1

#include <TransitionListener.h>

#define MAX_STATES 8
#define MAX_LISTENERS 4

class TransitionNotifier {
    
  static TransitionListener *listeners[MAX_STATES][MAX_STATES][MAX_LISTENERS];

public:

  TransitionNotifier();

  void addTransitionListener(unsigned char fromState, unsigned char toState, TransitionListener *listener);

  void notifyTransition(unsigned char fromState, unsigned char toState);
};

#endif /* RDIONO_PARKING_SENSOR_TRANSITION_NOTIFIER__ */