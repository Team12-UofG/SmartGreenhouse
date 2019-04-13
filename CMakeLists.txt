cmake_minimum_required(VERSION 3.13)
project(SmartGreenhouse)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/Environment_sensor)
include_directories(include/Soil_sensor)
include_directories(include/UV_sensor)
include_directories(test)

add_executable(SmartGreenhouse
    include/Environment_sensor/bme680.h
    include/Environment_sensor/bme680_defs.h
    include/Soil_sensor/MCP342X.cpp
    include/Soil_sensor/MCP342X.h
    include/UV_sensor/LEDMATRIX.cpp
    include/UV_sensor/LEDMATRIX.h
    include/UV_sensor/VEML6075.cpp
    include/UV_sensor/VEML6075.h
    test/preliminary/Environment_sensor/bme680.c
    test/preliminary/Environment_sensor/readEnvironment.cpp
    test/preliminary/Soil_sensor/printSoilValues.cpp
    test/preliminary/Soil_sensor/SensorPump.cpp
    test/preliminary/Soil_sensor/Soiltest.cpp
    test/preliminary/UV_sensor/printUVValues.cpp
    test/preliminary/UV_sensor/UVcontrol_LEDs.cpp
    test/preliminary/bme680.c
    test/preliminary/master.cpp
    test/preliminary/readall.cpp
    test/unit/manual_op/heatmat.cpp
    test/unit/manual_op/heatmatoff.cpp
    test/unit/manual_op/ledon.cpp
    test/unit/manual_op/waterpump.cpp
    test/unit/manual_op/waterpumpoff.cpp
    test/unit/environment_sensor.cpp
    test/unit/outputs.cpp
    test/unit/soil_sensor.cpp
    test/unit/uv_sensor.cpp)
