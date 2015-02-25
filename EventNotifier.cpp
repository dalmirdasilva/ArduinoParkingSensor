
#include <EventNotifier.h>

EventListener *EventNotifier::listeners[MAX_LISTENERS] = {};

void EventNotifier::addEventListener(EventListener *listener) {
    if (index < MAX_LISTENERS - 1) {
        listeners[index++] = listener;
    }
}

void EventNotifier::removeEventListener(EventListener *listener) {
    unsigned char i, found = 0;
    for (i = 0; i < MAX_LISTENERS; i++) {
        if (found == 0) {
            if (listeners[i] == listener) {
                found = 1;
            }
        } else {
            listeners[i] = i == MAX_LISTENERS - 1 ? listener[i + 1];
        }
    }
}

void EventNotifier::notify(unsigned char event) {
    for (i = 0; i < index; i++) {
        listeners[i].eventReceived(event);
    }
}
