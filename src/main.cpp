#include <string>
#include <iostream>
#include <cstdio>
#include <stdlib.h>     /* atoi */


#include <unistd.h>

#include "serial/serial.h"

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

std::vector<float> laser_measurements;
std::vector<int> laser_intensities;

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void print_usage()
{
	cerr << "Usage: test_serial <serial port address>";
    cerr << "<baudrate>" << endl;
}

int run(int argc, char **argv)
{
  if(argc < 2) {
	  print_usage();
    return 0;
  }

  // Argument 1 is the serial port or enumerate flag
  string port(argv[1]);

  else if( argc < 3 ) {
	  print_usage();
	  return 1;
  }

  // Argument 2 is the baudrate
  unsigned long baud = 0;

  sscanf(argv[2], "%lu", &baud);

  // port, baudrate, timeout in milliseconds
  serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000), serial::eightbits, serial::parity_none, serial::stopbits_one);

  laser_measurements.resize(360);
  laser_intensities.resize(360);

  cout << "Is the serial port open?";
  if(my_serial.isOpen())
    cout << " Yes." << endl;
  else
    cout << " No." << endl;

  ros::init(argc, argv, "precaster_laser2d_publisher");
  ros::NodeHandle n;
  ros::Publisher laser_pub = n.advertise<sensor_msgs::LaserScan>("scan", 1);

  sensor_msgs::LaserScan laser_scan;
  laser_scan.angle_min = 0;
  laser_scan.angle_max = 360;
  laser_scan.angle_increment = 1*3.14/180;
  laser_scan.range_min = 0.1;
  laser_scan.range_max = 6;
  laser_scan.ranges.resize(360);
  laser_scan.intensities.resize(360);

  while (1) {

    string result = my_serial.read(1);
    if(result.length()==0)
      continue;
    std::vector<uint> bytes(result.begin(), result.end());

    if(bytes[0]==0xFA){
      std::vector<uint> read_bytes;
      while(1){
        string data = my_serial.read(1);
        std::vector<uint> byte(data.begin(), data.end());
        read_bytes.push_back(byte[0]);
        if(read_bytes.size()==21){
          break;
        }
      }

      int angle = read_bytes[0]*4;
      int rpm = (read_bytes[2] << 8) + read_bytes[1];

      int distance1 = (read_bytes[4] << 8) + read_bytes[3];
      int signal1 = (read_bytes[6] << 8) + read_bytes[5];

      int distance2 = (read_bytes[8] << 8) + read_bytes[7];
      int signal2 = (read_bytes[10] << 8) + read_bytes[9];

      int distance3 = (read_bytes[12] << 8) + read_bytes[11];
      int signal3 = (read_bytes[14] << 8) + read_bytes[13];

      int distance4 = (read_bytes[16] << 8) + read_bytes[15];
      int signal4 = (read_bytes[18] << 8) + read_bytes[17];
      if(angle==0)
      printf("%d %d %d %d %d %d\n", angle, rpm, distance1, distance2, distance3, distance4);

      laser_measurements[angle] = distance1/1000.0;
      laser_measurements[angle+1] = distance2/1000.0;
      laser_measurements[angle+2] = distance3/1000.0;
      laser_measurements[angle+3] = distance4/1000.0;

      laser_intensities[angle] = signal1;
      laser_intensities[angle+1] = signal2;
      laser_intensities[angle+2] = signal3;
      laser_intensities[angle+3] = signal4;

      if(angle==0){
        for(int j = 0; j < laser_measurements.size(); j++){
          laser_scan.ranges[j] = laser_measurements[j];
          laser_scan.intensities[j] = laser_intensities[j];
        }
        laser_pub.publish(laser_scan);
      }
    }
  }
  return 0;
}

int main(int argc, char **argv)
{
  try {
    return run(argc, argv);
  } catch (exception &e) {
    cerr << "Unhandled Exception: " << e.what() << endl;
  }
}
