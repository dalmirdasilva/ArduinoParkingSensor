#include <EventNotifier.h>

EventListener *EventNotifier::listeners[MAX_EVENTS][MAX_LISTENERS] = {};

EventNotifier::EventNotifier() {
  unsigned char i, j;
  for (i = 0; i < MAX_EVENTS; i++) {
    for (j = 0; j < MAX_LISTENERS; j++) {
      listeners[i][j] = 0;
    }
  }
}

void EventNotifier::addEventListener(unsigned char event, EventListener *listener) {
  unsigned char i;
  for (i = 0; i < MAX_LISTENERS; i++) {
    if (listeners[event][i] != 0) {
      listeners[event][i] = listener;
      return;
    }
  }
}

void EventNotifier::notify(unsigned char event) {
  unsigned char i;
  for (i = 0; i < i; i++) {
    listeners[event][i]->eventReceived();
  }
}
