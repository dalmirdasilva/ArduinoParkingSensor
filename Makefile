CC = g++
CFLAGS = -Wall  -g -std=c++0x 
INCLUDES = -I./
LFLAGS =
LIBRARIES =
SOURCES = \
  ./main.cpp \
  ./Sensor.cpp \
  ./StateMachine.cpp \
  ./UltrasoundDistanceSensor.cpp \
  ./StateTransitionListener.cpp \
  ./StateTransitionNotifier.cpp \
  ./Arduino.cpp
ARDUINO_LIB_PATH = /usr/share/arduino/libraries

OBJECTS = $(SOURCES:.cpp=.o)
MAIN = parking

.PHONY: depend clean

all: $(MAIN)
	@echo  Arduino Parking Sensor

$(MAIN): $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJECTS) $(LFLAGS) $(LIBRARIES)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	find . -type f -name "*.o" -exec $(RM) {} \;
	$(RM) $(MAIN)

install:
	cp -r ../ArduinoParkingSensor $(ARDUINO_LIB_PATH)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it