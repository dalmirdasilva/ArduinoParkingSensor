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

  Sensor sensor0(&distanceSensor0, 3.0f);
  Sensor sensor1(&distanceSensor1, 3.0f);

  sensors[0] = &sensor0;
  sensors[1] = &sensor1;

  stateTable[0][Sensor::SensorState::PRESENT][SensorManager::IDLE] = SensorManager::IDLE;
  stateTable[0][Sensor::SensorState::ABSENT][SensorManager::IDLE] = SensorManager::IDLE;

  SensorManager manager(&sensors[0], &stateTable[0][0][0]);

  manager.addTransitionListener(SensorManager::ARRIVE2, SensorManager::IDLE, (TransitionListener *)&arriveHandler);
  manager.addTransitionListener(SensorManager::LEAVE2, SensorManager::IDLE, (TransitionListener *)&leaveHandler);

  manager.start();

  return 0;
}
