#include <StateTransitionListener.h>
#include <Settings.h>
#include <Sensor.h>
#include <StateMachine.h>
#include <UltrasoundDistanceSensor.h>
#include <ArduinoLedMatrix>
#include <Arduino.h>


#define SENSOR0_TRIG_PIN  A0
#define SENSOR0_ECHO_PIN  A1
#define SENSOR1_TRIG_PIN  A2
#define SENSOR1_ECHO_PIN  A3

#define SENSOR0_MIN_DISTANCE  1.0
#define SENSOR0_MAX_DISTANCE  400.0
#define SENSOR0_THRESHOLD     4.0
#define SENSOR1_MIN_DISTANCE  1.0
#define SENSOR1_MAX_DISTANCE  400.0
#define SENSOR1_THRESHOLD     4.0

class EventHandler : public StateTransitionListener {

public:
  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    Serial.print("State transitioned from ");
    Serial.print(fromState, HEX);
    Serial.print(" to ");
    Serial.println(toState, HEX);
  }
};

class LeaveHandler : public StateTransitionListener {

public:
  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    Serial.println("Saiu");
  }
};

class ArriveHandler : public StateTransitionListener {

public:
  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    Serial.println("Entrou");
  }
};

void setup() {

  Serial.begin(9600);
  Serial.println("Initializing.");

  ArriveHandler arriveHandler;
  LeaveHandler leaveHandler;
  EventHandler eventHandler;

  Sensor *sensors[MAX_SENSORS];

  unsigned char i, j, stateTable[MAX_SENSORS][MAX_EVENTS][MAX_STATES] = {StateMachine::UNDEFINED};

  UltrasoundDistanceSensor distanceSensor0(SENSOR0_ECHO_PIN, SENSOR0_TRIG_PIN);
  UltrasoundDistanceSensor distanceSensor1(SENSOR1_ECHO_PIN, SENSOR1_TRIG_PIN);

  Sensor sensor0(&distanceSensor0, SENSOR0_THRESHOLD, SENSOR0_MIN_DISTANCE, SENSOR0_MAX_DISTANCE);
  Sensor sensor1(&distanceSensor1, SENSOR1_THRESHOLD, SENSOR1_MIN_DISTANCE, SENSOR1_MAX_DISTANCE);

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

  stateMachine.addStateTransitionListener(StateMachine::ARRIVE2, StateMachine::IDLE, &arriveHandler);
  stateMachine.addStateTransitionListener(StateMachine::LEAVE2, StateMachine::IDLE, &leaveHandler);

  for (i = 0; i < MAX_STATES; i++) {
    for (j = 0; j < MAX_STATES; j++) {
      //stateMachine.addStateTransitionListener((StateMachine::State)i, (StateMachine::State)j, &eventHandler);
    }
  }

  Serial.println("Done. Starting machine state...");
  stateMachine.start();
}

void loop() {}

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
