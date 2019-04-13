cmake_minimum_required(VERSION 3.7)
project(SmartGreenhouse)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/Environment_sensor)
include_directories(include/Soil_sensor)
include_directories(include/UV_sensor)
include_directories(test)
include_directories(/usr/include/mysql/)

set(CMAKE_CXX_FLAGS "-lwiringPi" "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(SmartGreenhouse
    test/preliminary/bme680.c
    test/preliminary/readallv2.cpp
    )
