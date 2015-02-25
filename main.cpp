#include <pthread.h>

#include <ArduinoParkingSensor.h>
#include <EventListener.h>
#include <EventNotifier.h>

#include <main.h>

int main(int argc, char* argv[]) {
  int arg = 0;
  void *exit_status;

  glutInit(&argc,argv);
  pthread_t cube_thread, effect_runner_thread;

  pthread_create(&cube_thread, NULL, cubeInit, &arg);
  pthread_create(&effect_runner_thread, NULL, effect_runner, &arg);

  pthread_join(cube_thread, &exit_status);
  pthread_join(effect_runner_thread, &exit_status);

  return 0;
}
