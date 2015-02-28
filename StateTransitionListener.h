#ifndef __ARDUINO_PARKING_SENSOR_TRANSITION_LISTENER__
#define __ARDUINO_PARKING_SENSOR_TRANSITION_LISTENER__ 1

class StateTransitionListener {
    
public:

    virtual void eventReceived() = 0;
};

#endif /* __ARDUINO_PARKING_SENSOR_TRANSITION_LISTENER__ */