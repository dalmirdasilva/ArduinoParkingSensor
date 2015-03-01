#ifndef __ARDUINO_PARKING_SENSOR_ARDUINO__
#define __ARDUINO_PARKING_SENSOR_ARDUINO__ 1

#define INPUT 1
#define OUTPUT 0
#define LOW 0
#define HIGH 0

void pinMode(unsigned char pin, unsigned char mode);
void digitalWrite(unsigned char pin, unsigned char state);
void delayMicroseconds(int millis);
unsigned long pulseIn(unsigned char pin, unsigned char state, int timeout);

#endif /* __ARDUINO_PARKING_SENSOR_ARDUINO__ */