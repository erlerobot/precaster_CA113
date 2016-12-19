#include "CA113A.hpp"

int run(int argc, char **argv)
{
	ros::init(argc, argv, "precaster_laser2d_publisher");

	// Argument 1 is the serial port or enumerate flag
  ros::NodeHandle pnh("~");
  std::string port;
  pnh.param<std::string>("port", port, "/dev/ttyAMA");

  // Argument 2 is the baudrate
  int baud = 0;
  pnh.param<int>("baudrate", baud, 230400);

	CA113A laser2D(port, baud);

  while (1) {
		laser2D.read_message();
  }
  return 0;
}

int main(int argc, char **argv)
{
  try {
    return run(argc, argv);
  } catch (std::exception &e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
  }
}
