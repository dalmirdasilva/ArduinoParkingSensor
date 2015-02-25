#include <Arduino.h>
#include <stdio.h>

void pinMode(unsigned char pin, unsigned char mode) {
}

void digitalWrite(unsigned char pin, unsigned char state) {
}

void delayMicroseconds(int millis) {
}

int pulseIn(unsigned char pin, unsigned char state, unsigned char timeout) {
  int pulse = 0;
  printf("pin: %d, state: %d, timeout: %d\n", pin, state, timeout);
  scanf("%d", &pulse);
  return pulse;
}
