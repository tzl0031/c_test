cmake_minimum_required(VERSION 3.5)
project(multithread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    multithread/FileUtil.h
#    multithread/raspberry_osio_client.cpp
#        multithread/raspberry_osio_client.h
    multithread/Sensor.h
    multithread/test.cpp
        multithread/Communicator.h
        multithread/Communicator.cpp
        multithread/Sensor.cpp
        multithread/FileUtil.cpp
#        multithread/config.json
        )

#create target
add_executable(multithread ${SOURCE_FILES})

#add header directories
include_directories(src/mosquitto-1.4.5/lib)
include_directories(src/mosquitto-1.4.5/lib/cpp)
include_directories(src/jsoncpp/include)
#include_directories(src/raspberry-pi-mqtt/raspberry_osio_client)

link_directories(src/mosquitto-1.4.5/lib)


#link_directories(/src/jsoncpp/libs)
link_directories(src/jsoncpp)
#target_link_libraries(multithread json)

target_link_libraries(multithread json_linux-gcc-5.4.0_libmt)
target_link_libraries(multithread mosquitto)
target_link_libraries(multithread mosquittopp)


#target_link_libraries(multithread libmosquitto)