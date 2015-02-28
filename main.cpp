#include <stdio.h>
#include "StateTransitionListener.h"
#include "Settings.h"
#include "Sensor.h"
#include "StateMachine.h"

class LeaveHandler : public StateTransitionListener {

public:
  virtual void eventReceived() {
    printf("Leave");
  }
};

class ArriveHandler : public StateTransitionListener {

public:
  virtual void eventReceived() {
    printf("Arrive");
  }
};

int main(int argc, char* argv[]) {

  ArriveHandler arriveHandler;
  LeaveHandler leaveHandler;

  Sensor *sensors[MAX_SENSORS];

  unsigned char stateTable[MAX_SENSORS][MAX_EVENTS][MAX_STATES] = {StateMachine::State::UNDEFINED};

  UltrasoundDistanceSensor distanceSensor0(0, 1);
  UltrasoundDistanceSensor distanceSensor1(0, 2);

  Sensor sensor0(&distanceSensor0, 2.0f, 0.0f);
  Sensor sensor1(&distanceSensor1, 2.0f, 0.0f);

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

  stateMachine.addStateTransitionListener(StateMachine::State::ARRIVE2, StateMachine::State::IDLE, (StateTransitionListener *)&arriveHandler);
  stateMachine.addStateTransitionListener(StateMachine::State::LEAVE2, StateMachine::State::IDLE, (StateTransitionListener *)&leaveHandler);

  stateMachine.start();

  return 0;
}
