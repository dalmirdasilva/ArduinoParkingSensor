/**
 * Arduino - Distance sensor
 * 
 * DistanceSensor.h
 * 
 * The abstract class for the distance sensors.
 * 
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_DISTANCE_SENSOR_H__
#define __ARDUINO_DRIVER_DISTANCE_SENSOR_H__ 1

class DistanceSensor {
public:

    virtual ~DistanceSensor();

    /**
     * Gets the distance o the device from whatever is in front of it.
     * 
     * @retun   The distance in centimeters.
     */
    virtual float getDistance() = 0;
};

#endif /* __ARDUINO_DRIVER_DISTANCE_SENSOR_H__ */
