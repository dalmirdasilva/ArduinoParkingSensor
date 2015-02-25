CC = g++
CFLAGS = -Wall  -g -std=c++0x 
INCLUDES = -I./
LFLAGS =
LIBRARIES = -lpthread
SOURCES = \
  ./main.cpp \
  ./ArduinoParkingSensor.cpp \
  ./EventListener.cpp \
  ./EventNotifier.cpp

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

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
