# ArduinoParkingSensor

[Documentation.pdf](Documentation.pdf)

## Objective

Detect when a car arrives or leaves the parking lot.

## Wiring

The Ultrasonic Sensor are attached to the pins:

- SENSOR0_TRIG_PIN  A0
- SENSOR0_ECHO_PIN  A1
- SENSOR1_TRIG_PIN  A2
- SENSOR1_ECHO_PIN  A3

A 8x8 led amtrix is attached to:

- LED_MATRIX_DATA_PIN   10
- LED_MATRIX_CLOCK_PIN  11
- LED_MATRIX_LOAD_PIN   12

## How it works

A machine state is used to determine if the car is arriving or leaving the parking lot.
