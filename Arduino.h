#ifndef __ARDIONO_PARKING_SENSOR_ARDUINO__
#define __ARDIONO_PARKING_SENSOR_ARDUINO__ 1


void pinMode(unsigned char pin, unsigned char mode);
void digitalWrite(unsigned char pin, unsigned char state);
void delayMicroseconds(int millis);
int pulseIn(unsigned char pin, unsigned char state, unsigned char timeout);

#endif /* __ARDIONO_PARKING_SENSOR_ARDUINO__ */