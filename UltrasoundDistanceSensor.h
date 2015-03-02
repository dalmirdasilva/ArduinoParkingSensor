/**
 * Arduino - Ultrasound distance sensor
 * 
 * UltrasoundDistanceSensor.h
 * 
 * The abstract class for the ultrasound distance sensor.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_ULTRASOUND_DISTANCE_SENSOR_H__
#define __ARDUINO_DRIVER_ULTRASOUND_DISTANCE_SENSOR_H__ 1

#include <DistanceSensor.h>
#include <Arduino.h>

#define ULTRASOUND_DISTANCE_SENSOR_MAX_DISTANCE_CM 300.0

/**
 * Centimeters per microsecond.
 */
#define US_SENSOR_CM_PER_US 0.03463

/** 
 * Microseconds in 1 centimeter.
 * 
 * (1/US_SENSOR_CM_PER_US)
 */
#define US_SENSOR_US_PER_CM 28.8

/**
 * Doubles the time, counting the time to go and back.
 * 
 * (US_SENSOR_US_PER_CM*2)
 */
#define US_SENSOR_2_TIMES_US_PER_CM 57.7

/**
 * 2 meters
 * How many microseconds can wait. Enough to go and back 3 meters of distance.
 * 
 * (US_SENSOR_2_TIMES_US_PER_CM*ULTRASOUND_DISTANCE_SENSOR_MAX_DISTANCE_CM)
 */
#define US_SENSOR_PULSE_IN_TIMEOUT 17310.0

class UltrasoundDistanceSensor : public DistanceSensor {
private:

    /**
     * The echo pin.
     */
    unsigned char echoPin;

    /**
     * The trig pin.
     */
    unsigned char trigPin;

public:

    /**
     * Public constructor.
     * 
     * @param echoPin   The echo pin.
     * @param trigPin   The trigger pin.
     */
    UltrasoundDistanceSensor(unsigned char echoPin, unsigned char trigPin);

    /**
     * Gets the time between the send and reice the sound.
     * 
     * @return   The time between the send and reice the sound.
     */
    unsigned long getEchoTime();

    /**
     * Gets the distance o the device from whatever is in front of it.
     * 
     * @return   The distance in centimeters.
     */
    float getDistance();
};

#endif /* __ARDUINO_DRIVER_ULTRASOUND_DISTANCE_SENSOR_H__ */
