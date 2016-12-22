# precaster_laser2D

[CA113](https://www.precaster.com.tw/predustrial/ca113/) is designed as a compact and reliable 2D laser distance measuring sensor. The pulse technology gives the good accuracy and response time in distance measuring and a stable output under strong ambient light.

![](https://www.precaster.com.tw/predustrial/wp-content/uploads/2016/08/CA113_img4.png)

### Features

 - Highly Customizable module fit for most duties.
 - Adjustable High Speed measuring up to 1800HZ.
 - Digital output with UART.
 - TOF Non-Contact Measuring Low Consumption Sensor.
 - Light Communication for Data transmission.
 - Ultra Durable Rotary Base.

### Applications

 - Robot eyes distance measuring
 - Positioning and monitor of objects
 - Security applications movement detections
 - Level and elevator measuring
 - Drone dodge action control
 - 2D scanning and mapping

| Model No. | CA113 Spec. | CA113 Tolerance|
| --- | --- | --- |
| Maximun measuring range| 6 meters | 6.5m |
| Minimum Measuring Range|  0.1 meters | 0.05m|
|  Repeatability Accuracy from 0.5m to 1m |  ±20 mm|  Standard Deviation 2σ, Kodak White Board|
| Repeatability Accuracy from 1m to 5m | ±40 mm|
| Repeatability Accuracy over 6m	 | ±1% of measured distance | |
| Measurement Time | 1800 Hz| |
| Unit		| Millimeter| |
| Power Source		| 12V|  ±0.2V|
| Power Consumption		| 2W | |
| Laser Radiation		| Class 1| |
| Laser Wavelength		| 808nm| |
| Rotation Speed		| 300rpm| ±30rpm|
| Rotation Angle Resolution		| 1°| |
| Rotation Angle Accuracy		| ±0.5° | |
| Operating Temperature Range		| -5°C~40°C| |
| Storage Temperature Range		| -20°C~60°C| |
| Serial Port Type		| UART| | |
| Dimensions		| 61 x 21 x 18 mm| |
| Weight		| 17.6g| ±5g | |

## Configuring precaster 2D laser CA113A

Make sure that your node is able to access the data from the sensor

List the permissions of your serial port, for example in a Rpi2:

```
ls -l /dev/ttyAMA0
```

You will see something like to:

```
crw-rw-XX- 1 root dialout 204, 64 Dec 16 10:17 /dev/ttyAMA0
```

If **XX** is `rw`: the sensor is configured properly.

If **XX** is `--`: the sensor is not configured properly and you need to:

```
sudo chmod a+rw /dev/ttyAMA0
```

## Compiling the code

Clone this repository in a ROS 2.0 workspace

```
cd ~/ros2_ws/src
git clone https://github.com/erlerobot/precaster_laser2d -b ros2
```
Now compile the code:

```
cd ~/ros2_ws/
source ~/ros2_ws/install/setup.bash
ament build --only-package precaster_ca113a
```

## Execute

In other terminal source your ROS 2.0 workspace

```
source ~/ros2_ws/install/setup.bash
```
Now launch your ROS 2.0 driver:
```
precaster_ca113a /dev/ttyAMA0 230400
```
