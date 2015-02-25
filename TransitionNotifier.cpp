#include <TransitionNotifier.h>

TransitionListener *TransitionNotifier::listeners[MAX_STATES][MAX_STATES][MAX_LISTENERS] = {};

TransitionNotifier::TransitionNotifier() {
  unsigned char i, j, k;
  for (i = 0; i < MAX_STATES; i++) {
    for (j = 0; j < MAX_STATES; j++) {
      for (k = 0; k < MAX_LISTENERS; k++) {
        listeners[i][j][k] = 0;
      }
    }
  }
}

void TransitionNotifier::addTransitionListener(unsigned char fromState, unsigned char toState, TransitionListener *listener) {
  unsigned char i;
  for (i = 0; i < MAX_LISTENERS; i++) {
    if (listeners[fromState % MAX_STATES][toState % MAX_STATES][i] != 0) {
      listeners[fromState % MAX_STATES][toState % MAX_STATES][i] = listener;
      return;
    }
  }
}

void TransitionNotifier::notify(unsigned char fromState, unsigned char toState) {
  unsigned char i;
  for (i = 0; i < i; i++) {
    listeners[fromState % MAX_STATES][toState % MAX_STATES][i]->eventReceived();
  }
}
