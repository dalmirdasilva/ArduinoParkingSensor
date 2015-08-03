#include <StateTransitionListener.h>
#include <Settings.h>
#include <Sensor.h>
#include <StateMachine.h>
#include <UltrasoundDistanceSensor.h>
#include <Arduino.h>

#include <string.h>

#include <MAX7219Driver.h>
#include <LedMatrixDriver.h>
#include <LedMatrixMAX7219Driver.h>

#define SENSOR0_TRIG_PIN  A0
#define SENSOR0_ECHO_PIN  A1
#define SENSOR1_TRIG_PIN  A2
#define SENSOR1_ECHO_PIN  A3

#define SENSOR0_MIN_DISTANCE  0.0
#define SENSOR0_MAX_DISTANCE  400.0
#define SENSOR0_THRESHOLD     40.0
#define SENSOR1_MIN_DISTANCE  0.0
#define SENSOR1_MAX_DISTANCE  400.0
#define SENSOR1_THRESHOLD     40.0

#define LED_MATRIX_WIDTH      8
#define LED_MATRIX_HEIGHT     8

#define LED_MATRIX_DATA_PIN   10
#define LED_MATRIX_CLOCK_PIN  11
#define LED_MATRIX_LOAD_PIN   12

unsigned char parkingCounter = 0;

class LedMatrixWriter {

  LedMatrixMAX7219Driver *matrix;

public:

  LedMatrixWriter(LedMatrixMAX7219Driver *matrix) :
      matrix(matrix) {
  }

  LedMatrixMAX7219Driver *getMatrix() {
    return matrix;
  }
};

class EventHandler : public StateTransitionListener, public LedMatrixWriter {

public:

  EventHandler(LedMatrixMAX7219Driver *matrix) :
      LedMatrixWriter(matrix) {
  }

  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    Serial.print("State transitioned from ");
    Serial.print(fromState, HEX);
    Serial.print(" to ");
    Serial.println(toState, HEX);
    getMatrix()->setCol(0, toState);
  }
};

class LeaveHandler : public StateTransitionListener, public LedMatrixWriter {

public:

  LeaveHandler(LedMatrixMAX7219Driver *matrix) :
      LedMatrixWriter(matrix) {
  }

  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    if (parkingCounter > 0) {
      parkingCounter--;
    }
    Serial.println("Leaved.");
    getMatrix()->setCol(7, parkingCounter);
  }
};

class ArriveHandler : public StateTransitionListener, public LedMatrixWriter {

public:

  ArriveHandler(LedMatrixMAX7219Driver *matrix) :
      LedMatrixWriter(matrix) {
  }

  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    if (parkingCounter < 0xff) {
      parkingCounter++;
    }
    Serial.println("Arrived.");
    getMatrix()->setCol(7, parkingCounter);
  }
};

void setup() {

  Serial.begin(9600);
  Serial.print("Initializing...");

  MAX7219Driver driver(LED_MATRIX_DATA_PIN, LED_MATRIX_CLOCK_PIN, LED_MATRIX_LOAD_PIN);
  LedMatrixMAX7219Driver matrix(&driver, LED_MATRIX_WIDTH, LED_MATRIX_HEIGHT);

  ArriveHandler arriveHandler(&matrix);
  LeaveHandler leaveHandler(&matrix);
  EventHandler eventHandler(&matrix);

  Sensor *sensors[MAX_SENSORS];

  UltrasoundDistanceSensor distanceSensor0(SENSOR0_ECHO_PIN, SENSOR0_TRIG_PIN);
  UltrasoundDistanceSensor distanceSensor1(SENSOR1_ECHO_PIN, SENSOR1_TRIG_PIN);

  Sensor sensor0(&distanceSensor0, SENSOR0_THRESHOLD, SENSOR0_MIN_DISTANCE, SENSOR0_MAX_DISTANCE);
  Sensor sensor1(&distanceSensor1, SENSOR1_THRESHOLD, SENSOR1_MIN_DISTANCE, SENSOR1_MAX_DISTANCE);

  unsigned char i, j, stateTable[MAX_SENSORS][MAX_EVENTS][MAX_STATES];
  memset(stateTable, StateMachine::UNDEFINED, sizeof(stateTable));

  sensors[0] = &sensor0;
  sensors[1] = &sensor1;

  stateTable[0][Sensor::PRESENT][StateMachine::IDLE] = StateMachine::ARRIVE0;
  stateTable[0][Sensor::PRESENT][StateMachine::LEAVE0] = StateMachine::LEAVE1;
  stateTable[0][Sensor::PRESENT][StateMachine::ARRIVE2] = StateMachine::ARRIVE1;

  stateTable[0][Sensor::ABSENT][StateMachine::ARRIVE0] = StateMachine::IDLE;
  stateTable[0][Sensor::ABSENT][StateMachine::ARRIVE1] = StateMachine::ARRIVE2;
  stateTable[0][Sensor::ABSENT][StateMachine::LEAVE1] = StateMachine::LEAVE0;
  stateTable[0][Sensor::ABSENT][StateMachine::LEAVE2] = StateMachine::IDLE;

  stateTable[1][Sensor::PRESENT][StateMachine::IDLE] = StateMachine::LEAVE0;
  stateTable[1][Sensor::PRESENT][StateMachine::ARRIVE0] = StateMachine::ARRIVE1;
  stateTable[1][Sensor::PRESENT][StateMachine::LEAVE2] = StateMachine::LEAVE1;

  stateTable[1][Sensor::ABSENT][StateMachine::LEAVE0] = StateMachine::IDLE;
  stateTable[1][Sensor::ABSENT][StateMachine::ARRIVE1] = StateMachine::ARRIVE0;
  stateTable[1][Sensor::ABSENT][StateMachine::ARRIVE2] = StateMachine::IDLE;
  stateTable[1][Sensor::ABSENT][StateMachine::LEAVE1] = StateMachine::LEAVE2;

  StateMachine stateMachine(&sensors[0], &stateTable[0][0][0], StateMachine::IDLE);

  for (i = 0; i < MAX_STATES; i++) {
    for (j = 0; j < MAX_STATES; j++) {
      stateMachine.addStateTransitionListener((StateMachine::State) i, (StateMachine::State) j, &eventHandler);
    }
  }

  stateMachine.addStateTransitionListener(StateMachine::ARRIVE2, StateMachine::IDLE, &arriveHandler);
  stateMachine.addStateTransitionListener(StateMachine::LEAVE2, StateMachine::IDLE, &leaveHandler);

  Serial.println("done. \nStarting machine state...");

  matrix.clear();
  stateMachine.start();
}

void loop() {

}

int main(void) {

  init();

#if defined(USBCON)
  USBDevice.attach();
#endif

  setup();

  while (true) {
    loop();
    if (serialEventRun) {
      serialEventRun();
    }
  }
}
