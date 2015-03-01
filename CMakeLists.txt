cmake_minimum_required(VERSION 2.8.4)
project(ArduinoParkingSensor)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(./)

set(SOURCE_FILES
    Arduino.cpp
    Arduino.h
    DistanceSensor.cpp
    DistanceSensor.h
    keywords
    main.cpp
    Makefile
    README.md
    Sensor.cpp
    Sensor.h
    Settings.h
    StateMachine.cpp
    StateMachine.h
    StateTransitionListener.cpp
    StateTransitionListener.h
    StateTransitionNotifier.cpp
    StateTransitionNotifier.h
    UltrasoundDistanceSensor.cpp
    UltrasoundDistanceSensor.h)

add_executable(ArduinoParkingSensor ${SOURCE_FILES})