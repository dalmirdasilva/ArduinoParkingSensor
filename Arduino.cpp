#include "Arduino.h"
#include <stdio.h>

void pinMode(unsigned char pin, unsigned char mode) {
}

void digitalWrite(unsigned char pin, unsigned char state) {
}

void delayMicroseconds(int millis) {
}

unsigned long pulseIn(unsigned char pin, unsigned char state, int timeout) {
  int pulse = 0;
  scanf("%d", &pulse);
  printf("pin: %d, state: %d, timeout: %d\n", pin, state, timeout);
  return pulse;
}
