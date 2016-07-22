cmake_minimum_required(VERSION 3.0)
project(multithread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    multithread/FileUtil.h
    multithread/Sensor.h
    multithread/test.cpp
    multithread/Communicator.h
    multithread/Communicator.cpp
    multithread/Sensor.cpp
    multithread/FileUtil.cpp
    multithread/config.json
#    multithread/create_json.h
        )



#create target
add_executable(multithread ${SOURCE_FILES})

#add header directories
include_directories(src/mosquitto-1.4.5/lib)
include_directories(src/mosquitto-1.4.5/lib/cpp)
include_directories(src/jsoncpp/include)

#link library directories
link_directories(src/mosquitto-1.4.5/lib)
link_directories(src/jsoncpp)

#link libraries to library
target_link_libraries(multithread json_linux-gcc-5.4.0_libmt)
target_link_libraries(multithread mosquitto)
target_link_libraries(multithread mosquittopp)


