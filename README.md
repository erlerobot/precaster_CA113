- [Precaster 2D laser CA113](#precaster-2d-laser-ca113)
 - [Features](#features)
 - [Applications](#applications)
 - [Technical data](#technical-data)
- [Configuring Precaster 2D laser CA113A](#configuring-precaster-2d-laser-ca113a)
- [Compiling the code from sources](#compiling-the-code-from-sources)
- [Launching manually](#launching-manually)
 - [Starting a roscore](#starting-a-roscore)
 - [Setting Parameters](#setting-parameters)
 - [Running Precaster 2D laser ca113a node](#running-precaster-2d-laser-ca113a-node)
- [Launch file](#launch-file)

# Precaster 2D laser CA113

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

### Technical data

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


## Configuring Precaster 2D laser CA113A

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

## Compiling the code from sources

Clone this repository in a ROS workspace or [create a new one](http://wiki.ros.org/catkin/Tutorials/create_a_workspace)

```
cd ~/ros_catkin_ws/src
git clone https://github.com/erlerobot/precaster_laser2d
```
Now compile the code:

```
cd ~/ros_catkin_ws/
catkin_make_isolated --install --pkg precaster_laser2d_ca113a
```

## Launching manually
### Starting a roscore

A roscore must be running:

```
roscore
```

### Setting Parameters

We need to make sure that we have the correct configurations loaded on the parameter server.

If your sensor is not at the default `/dev/ttyAMA` you have to indicate where it is below:

```
rosparam set /precaster_laser2d_ca113a/port /dev/ttyAMA0
```
The same idea with the baudrate:

```
rosparam set /precaster_laser2d_ca113a/baudrate 230400
```

### Running Precaster 2D laser ca113a node

```
rosrun precaster_laser2d_ca113a ca113a
```

## Launch file

```
roslaunch precaster_laser2d_ca113a ca113a.launch
```

If you need to modify some parameters just do it in the launch file.
