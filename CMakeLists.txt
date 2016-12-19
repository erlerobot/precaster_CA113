cmake_minimum_required(VERSION 2.8.3)

project(precaster_ca113a)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(serial REQUIRED)

macro(targets)
	if(NOT "${target_suffix} " STREQUAL " ")
		get_rclcpp_information("${rmw_implementation}" "rclcpp${target_suffix}")
	endif()

	add_executable(precaster_ca113a${target_suffix}
		src/main.cpp
		src/CA113A.cpp
	)
	ament_target_dependencies(precaster_ca113a${target_suffix}
	  "rclcpp${target_suffix}"
	  "sensor_msgs"
	  "serial"
	)

	install(TARGETS
			precaster_ca113a${target_suffix}
		  	DESTINATION bin)
endmacro()

call_for_each_rmw_implementation(targets GENERATE_DEFAULT)

ament_package()
