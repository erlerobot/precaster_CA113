#include "CA113A.hpp"

void print_usage()
{
	std::cerr << "Usage: test_serial <serial port address> ";
    std::cerr << "<baudrate>" << std::endl;
}

int run(int argc, char **argv)
{
	rclcpp::init(argc, argv);
  auto node = rclcpp::node::Node::make_shared("precaster_laser2d_ca113a_publisher");

  if( argc < 3 ) {
    print_usage();
    return -1;
  }
  // Argument 1 is the serial port or enumerate flag
  std::string port(argv[1]);

  // Argument 2 is the baudrate
  unsigned long baud = 0;
  sscanf(argv[2], "%lu", &baud);

	CA113A laser2D(port, baud, node);

  while (1) {
		laser2D.read_and_send_message();
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
