#include <UltrasoundDistanceSensor.h>
#include <TransitionListener.h>
#include <SensorManager.h>
#include <Sensor.h>
#include <stdio.h>

class LeaveHandler : public TransitionListener {

public:
  virtual void eventReceived() {
    printf("Leave");
  }
};

class ArriveHandler : public TransitionListener {

public:
  virtual void eventReceived() {
    printf("Arrive");
  }
};

int main(int argc, char* argv[]) {

  ArriveHandler arriveHandler;
  LeaveHandler leaveHandler;

  Sensor *sensors[MAX_SENSORS];

  unsigned char stateTable[MAX_SENSORS][MAX_EVENTS][MAX_STATES] = {SensorManager::UNDEFINED};

  UltrasoundDistanceSensor distanceSensor0(0, 1);
  UltrasoundDistanceSensor distanceSensor1(0, 2);

  Sensor sensor0(&distanceSensor0, 0.0f, 4.0f, 2.0f);
  Sensor sensor1(&distanceSensor1, 0.0f, 4.0f, 2.0f);

  sensors[0] = &sensor0;
  sensors[1] = &sensor1;

  stateTable[0][Sensor::SensorState::PRESENT][SensorManager::IDLE] = SensorManager::ARRIVE0;
  stateTable[0][Sensor::SensorState::PRESENT][SensorManager::LEAVE0] = SensorManager::LEAVE1;
  stateTable[0][Sensor::SensorState::PRESENT][SensorManager::ARRIVE2] = SensorManager::ARRIVE1;

  stateTable[0][Sensor::SensorState::ABSENT][SensorManager::ARRIVE0] = SensorManager::IDLE;
  stateTable[0][Sensor::SensorState::ABSENT][SensorManager::ARRIVE1] = SensorManager::ARRIVE2;
  stateTable[0][Sensor::SensorState::ABSENT][SensorManager::LEAVE1] = SensorManager::LEAVE0;
  stateTable[0][Sensor::SensorState::ABSENT][SensorManager::LEAVE2] = SensorManager::IDLE;

  stateTable[1][Sensor::SensorState::PRESENT][SensorManager::IDLE] = SensorManager::LEAVE0;
  stateTable[1][Sensor::SensorState::PRESENT][SensorManager::ARRIVE0] = SensorManager::ARRIVE1;
  stateTable[1][Sensor::SensorState::PRESENT][SensorManager::LEAVE2] = SensorManager::LEAVE1;

  stateTable[1][Sensor::SensorState::ABSENT][SensorManager::LEAVE0] = SensorManager::IDLE;
  stateTable[1][Sensor::SensorState::ABSENT][SensorManager::ARRIVE1] = SensorManager::ARRIVE0;
  stateTable[1][Sensor::SensorState::ABSENT][SensorManager::ARRIVE2] = SensorManager::IDLE;
  stateTable[1][Sensor::SensorState::ABSENT][SensorManager::LEAVE1] = SensorManager::LEAVE2;

  SensorManager manager(&sensors[0], &stateTable[0][0][0], SensorManager::IDLE);

  manager.addTransitionListener(SensorManager::ARRIVE2, SensorManager::IDLE, (TransitionListener *)&arriveHandler);
  manager.addTransitionListener(SensorManager::LEAVE2, SensorManager::IDLE, (TransitionListener *)&leaveHandler);

  manager.start();

  return 0;
}
