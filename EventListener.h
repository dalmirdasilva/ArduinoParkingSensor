#ifndef __ARDIONO_PARKING_SENSOR_EVENT_LISTENER__
#define __ARDIONO_PARKING_SENSOR_EVENT_LISTENER__ 1

class EventListener {
    
public:

    virtual void eventReceived() = 0;
};

#endif /* __ARDIONO_PARKING_SENSOR_EVENT_LISTENER__ */