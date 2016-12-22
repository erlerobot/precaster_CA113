# precaster_laser2D

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
