cmake_minimum_required(VERSION 2.8.3)
project(precaster_laser2d_ca113a)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs std_msgs serial)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ca113a src/main.cpp src/CA113A.cpp)
target_link_libraries(ca113a ${catkin_LIBRARIES})
add_dependencies(ca113a precaster_laser2d_ca113a)

install(
	TARGETS ca113a
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
PATTERN ".git" EXCLUDE)
