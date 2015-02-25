#ifndef __ARDIONO_PARKING_SENSOR_EVENT_NOTIFIER__
#define __ARDIONO_PARKING_SENSOR_EVENT_NOTIFIER__ 1

#include <EventListener.h>

#define MAX_EVENTS 4
#define MAX_LISTENERS 4

class EventNotifier {
    
  static EventListener *listeners[MAX_EVENTS][MAX_LISTENERS];

public:

  EventNotifier();

  void addEventListener(unsigned char event, EventListener *listener);

  void notify(unsigned char event);
};

#endif /* RDIONO_PARKING_SENSOR_EVENT_NOTIFIER__ */