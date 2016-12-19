#ifndef CA113A_H
#define CA113A_H

#include <serial/serial.h>

//ROS 2.0
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>     /* atoi */
#include <unistd.h>

class CA113A
{
public:
  CA113A(std::string port,
         unsigned long baud,
         std::shared_ptr<rclcpp::node::Node> node);
  void read_and_send_message();

private:
  std::vector<float> laser_measurements;
  std::vector<int> laser_intensities;

  rclcpp::publisher::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr laser_pub;
  serial::Serial my_serial;
};

#endif // CA113A_H
