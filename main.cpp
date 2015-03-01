#include <stdio.h>
#include "StateTransitionListener.h"
#include "Settings.h"
#include "Sensor.h"
#include "StateMachine.h"
#include "UltrasoundDistanceSensor.h"

class EventHandler : public StateTransitionListener {

public:
  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    printf("State transitioned from %x to %x.\n", fromState, toState);
  }
};

class LeaveHandler : public StateTransitionListener {

public:
  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    printf("Leave\n");
  }
};

class ArriveHandler : public StateTransitionListener {

public:
  virtual void eventReceived(unsigned char fromState, unsigned char toState) {
    printf("Arrive\n");
  }
};

int main(int argc, char* argv[]) {

  ArriveHandler arriveHandler;
  LeaveHandler leaveHandler;
  EventHandler eventHandler;

  Sensor *sensors[MAX_SENSORS];

  unsigned char i, j, stateTable[MAX_SENSORS][MAX_EVENTS][MAX_STATES] = {StateMachine::State::UNDEFINED};

  UltrasoundDistanceSensor distanceSensor0(0, 1);
  UltrasoundDistanceSensor distanceSensor1(0, 2);

  Sensor sensor0(&distanceSensor0, 5.0, 0.0, 10.0);
  Sensor sensor1(&distanceSensor1, 5.0, 0.0, 10.0);

  sensors[0] = &sensor0;
  sensors[1] = &sensor1;

  stateTable[0][Sensor::State::PRESENT][StateMachine::State::IDLE] = StateMachine::State::ARRIVE0;
  stateTable[0][Sensor::State::PRESENT][StateMachine::State::LEAVE0] = StateMachine::State::LEAVE1;
  stateTable[0][Sensor::State::PRESENT][StateMachine::State::ARRIVE2] = StateMachine::State::ARRIVE1;

  stateTable[0][Sensor::State::ABSENT][StateMachine::State::ARRIVE0] = StateMachine::State::IDLE;
  stateTable[0][Sensor::State::ABSENT][StateMachine::State::ARRIVE1] = StateMachine::State::ARRIVE2;
  stateTable[0][Sensor::State::ABSENT][StateMachine::State::LEAVE1] = StateMachine::State::LEAVE0;
  stateTable[0][Sensor::State::ABSENT][StateMachine::State::LEAVE2] = StateMachine::State::IDLE;

  stateTable[1][Sensor::State::PRESENT][StateMachine::State::IDLE] = StateMachine::State::LEAVE0;
  stateTable[1][Sensor::State::PRESENT][StateMachine::State::ARRIVE0] = StateMachine::State::ARRIVE1;
  stateTable[1][Sensor::State::PRESENT][StateMachine::State::LEAVE2] = StateMachine::State::LEAVE1;

  stateTable[1][Sensor::State::ABSENT][StateMachine::State::LEAVE0] = StateMachine::State::IDLE;
  stateTable[1][Sensor::State::ABSENT][StateMachine::State::ARRIVE1] = StateMachine::State::ARRIVE0;
  stateTable[1][Sensor::State::ABSENT][StateMachine::State::ARRIVE2] = StateMachine::State::IDLE;
  stateTable[1][Sensor::State::ABSENT][StateMachine::State::LEAVE1] = StateMachine::State::LEAVE2;

  StateMachine stateMachine(&sensors[0], &stateTable[0][0][0], StateMachine::State::IDLE);

  stateMachine.addStateTransitionListener(StateMachine::State::ARRIVE2, StateMachine::State::IDLE, &arriveHandler);
  stateMachine.addStateTransitionListener(StateMachine::State::LEAVE2, StateMachine::State::IDLE, &leaveHandler);

  for (i = 0; i < MAX_STATES; i++) {
    for (j = 0; j < MAX_STATES; j++) {
      stateMachine.addStateTransitionListener((StateMachine::State)i, (StateMachine::State)j, &eventHandler);
    }
  }

  stateMachine.start();

  return 0;
}
