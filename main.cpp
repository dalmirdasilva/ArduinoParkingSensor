#include <UltrasoundDistanceSensor.h>
#include <SensorManager.h>
#include <Sensor.h>

int main(int argc, char* argv[]) {

  enum States {
    IDLE = 0x00,
    E0 = 0x01,
    E1 = 0x02
  };

  enum Events {
    ON_FINISH_ENTRY = 0x02,
    ON_FINISH_EXIT = 0x04
  };

  Sensor *sensors[4];

  UltrasoundDistanceSensor distanceSensor0(0, 1);
  UltrasoundDistanceSensor distanceSensor1(0, 2);

  Sensor sensor0(&distanceSensor0, 3.0f);
  Sensor sensor1(&distanceSensor1, 3.0f);

  sensors[0] = &sensor0;
  sensors[1] = &sensor1;

  unsigned char stateTable[2][2][6];

  stateTable[0][Sensor::SensorState::PRESENT][IDLE] = IDLE;


  SensorManager manager(&sensors[0], &stateTable[0][0][0]);
  //manager.setSensors(sensors);
  manager.start();

  return 0;
}
