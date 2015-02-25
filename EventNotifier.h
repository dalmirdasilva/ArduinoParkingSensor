/**
 * 
 * 
 * 
 */

#include <EventListener.h>

#define MAX_LISTENERS 4

class EventNotifier {
    
    EventListener *listeners[MAX_LISTENERS];
    unsigned char index = 0;

public:

    void addEventListener(EventListener *listener);
    
    void removeEventListener(EventListener *listener);
    
    void notify(unsigned char event);
};
