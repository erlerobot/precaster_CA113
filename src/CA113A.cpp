#include "CA113A.hpp"

CA113A::CA113A(std::string port,
               unsigned long baud,
               std::shared_ptr<rclcpp::node::Node> node)
 :my_serial(port,
            baud,
            serial::Timeout::simpleTimeout(1000),
            serial::eightbits,
            serial::parity_none,
            serial::stopbits_one)
{
  std::cout << "Is the serial port open?";
  if(my_serial.isOpen())
    std::cout << " Yes." << std::endl;
  else
    std::cout << " No." << std::endl;

  laser_measurements.resize(360);
  laser_intensities.resize(360);

  laser_pub = node->create_publisher<sensor_msgs::msg::LaserScan>("scan", rmw_qos_profile_sensor_data);
}

void CA113A::read_and_send_message()
{
  sensor_msgs::msg::LaserScan laser_scan;
  laser_scan.angle_min = 0;
  laser_scan.angle_max = 360;
  laser_scan.angle_increment = 1*3.14/180;
  laser_scan.range_min = 0.1;
  laser_scan.range_max = 6;
  laser_scan.ranges.resize(360);
  laser_scan.intensities.resize(360);

  std::string result = my_serial.read(1);

  if(result.length()==0)
    return;

  std::vector<uint> bytes(result.begin(), result.end());
  if(bytes[0]==0xFA){
    std::vector<uint> read_bytes;
    while(1){
      std::string data = my_serial.read(1);
      std::vector<uint> byte(data.begin(), data.end());
      read_bytes.push_back(byte[0]);
      if(read_bytes.size()==21){
        break;
      }
    }

    int angle = read_bytes[0]*4;
    //int rpm = (read_bytes[2] << 8) + read_bytes[1];

    int distance1 = (read_bytes[4] << 8) + read_bytes[3];
    int signal1 = (read_bytes[6] << 8) + read_bytes[5];

    int distance2 = (read_bytes[8] << 8) + read_bytes[7];
    int signal2 = (read_bytes[10] << 8) + read_bytes[9];

    int distance3 = (read_bytes[12] << 8) + read_bytes[11];
    int signal3 = (read_bytes[14] << 8) + read_bytes[13];

    int distance4 = (read_bytes[16] << 8) + read_bytes[15];
    int signal4 = (read_bytes[18] << 8) + read_bytes[17];

    laser_measurements[angle] = distance1/1000.0;
    laser_measurements[angle+1] = distance2/1000.0;
    laser_measurements[angle+2] = distance3/1000.0;
    laser_measurements[angle+3] = distance4/1000.0;

    laser_intensities[angle] = signal1;
    laser_intensities[angle+1] = signal2;
    laser_intensities[angle+2] = signal3;
    laser_intensities[angle+3] = signal4;

    if(angle==0){
      for(unsigned int j = 0; j < laser_measurements.size(); j++){
        laser_scan.ranges[j] = laser_measurements[j];
        laser_scan.intensities[j] = laser_intensities[j];
      }
      laser_pub->publish(laser_scan);
    }
  }
  return;
}
