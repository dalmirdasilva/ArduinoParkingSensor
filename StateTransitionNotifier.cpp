#include <StateTransitionListener.h>
#include <Settings.h>
#include <StateTransitionNotifier.h>

StateTransitionListener *StateTransitionNotifier::listeners[MAX_STATES][MAX_STATES][MAX_LISTENERS] = {};

StateTransitionNotifier::StateTransitionNotifier() {
  unsigned char i, j, k;
  for (i = 0; i < MAX_STATES; i++) {
    for (j = 0; j < MAX_STATES; j++) {
      for (k = 0; k < MAX_LISTENERS; k++) {
        listeners[i][j][k] = 0;
      }
    }
  }
}

void StateTransitionNotifier::addStateTransitionListener(unsigned char fromState, unsigned char toState, StateTransitionListener *listener) {
  unsigned char i;
  for (i = 0; i < MAX_LISTENERS; i++) {
    if (listeners[fromState % MAX_STATES][toState % MAX_STATES][i] == 0) {
      listeners[fromState % MAX_STATES][toState % MAX_STATES][i] = listener;
      return;
    }
  }
}

void StateTransitionNotifier::notifyStateTransition(unsigned char fromState, unsigned char toState) {
  unsigned char i;
  StateTransitionListener *listener;
  for (i = 0; i < MAX_LISTENERS; i++) {
    listener = listeners[fromState % MAX_STATES][toState % MAX_STATES][i];
    if (listener != 0) {
      listener->eventReceived(fromState, toState);
    }
  }
}
