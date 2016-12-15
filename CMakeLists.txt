cmake_minimum_required(VERSION 2.8.3)
project(ros_precaster_laser2d)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(laser2d src/main.cpp)
target_link_libraries(laser2d ${catkin_LIBRARIES} /usr/local/lib/libserial.so)
add_dependencies(laser2d ros_precaster_laser2d)
