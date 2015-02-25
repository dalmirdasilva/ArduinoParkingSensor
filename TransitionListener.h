#ifndef __ARDIONO_PARKING_SENSOR_TRANSITION_LISTENER__
#define __ARDIONO_PARKING_SENSOR_TRANSITION_LISTENER__ 1

class TransitionListener {
    
public:

    virtual void eventReceived() = 0;
};

#endif /* __ARDIONO_PARKING_SENSOR_TRANSITION_LISTENER__ */