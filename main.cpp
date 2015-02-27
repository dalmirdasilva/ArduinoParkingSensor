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

  enum States {
    IDLE = 0x00,
    ARRIVE0 = 0x01,
    ARRIVE1 = 0x02,
    ARRIVE2 = 0x04,
    LEAVE0 = 0x08,
    LEAVE1 = 0x10,
    LEAVE2 = 0x20,
    UNDEFINED = 0xff
  };

  enum Events {
    ON_ARRIVE = 0x02,
    ON_LEAVE = 0x04
  };

  ArriveHandler arriveHandler;
  LeaveHandler leaveHandler;

  Sensor *sensors[MAX_SENSORS];

  unsigned char stateTable[MAX_SENSORS][MAX_EVENTS][MAX_STATES] = {UNDEFINED};

  UltrasoundDistanceSensor distanceSensor0(0, 1);
  UltrasoundDistanceSensor distanceSensor1(0, 2);

  Sensor sensor0(&distanceSensor0, 3.0f);
  Sensor sensor1(&distanceSensor1, 3.0f);

  sensors[0] = &sensor0;
  sensors[1] = &sensor1;

  stateTable[0][Sensor::SensorState::PRESENT][IDLE] = IDLE;
  stateTable[0][Sensor::SensorState::ABSENT][IDLE] = IDLE;

  SensorManager manager(&sensors[0], &stateTable[0][0][0]);

  manager.addTransitionListener(ARRIVE2, IDLE, (TransitionListener *)&arriveHandler);
  manager.addTransitionListener(LEAVE2, IDLE, (TransitionListener *)&leaveHandler);

  manager.start();

  return 0;
}
