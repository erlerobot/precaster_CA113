#ifndef CA113A_H
#define CA113A_H

#include <serial/serial.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>     /* atoi */
#include <unistd.h>

class CA113A
{
public:
  CA113A(std::string port, unsigned long baud);
  void read_message();

private:
  std::vector<float> laser_measurements;
  std::vector<int> laser_intensities;

  ros::Publisher laser_pub;
  serial::Serial my_serial;
};

#endif // CA113A_H
