# RTO-ROS 2

This repository contains code for packages that enable ROS 2 support for the **Festo Robotino 3**.

This repo is verified to work on a host laptop which had Ubuntu 20.04 LTS with ROS2 Foxy.

The original code was taken from [dietriro's robotino repository](https://github.com/dietriro/rto_core) and adapted for ROS2

**Note:** Not all functionality has been enabled. North Star support, BHA support, and gripper support have been disabled.

## Installation instructions for Host PC
- Go to [[https://wiki.openrobotino.org/index.php?title=Robotino_OS]] and download the .deb files provided under Ubuntu 20.04 for robotino-dev, rec-rpc, and robotino-api2
- Install the .deb files
- Clone this repo into a ros2 workspace
- Do `colcon build`
- Source the workspace
- To bring up the robot, use `ros2 launch rto_bringup_launch.py hostname:=<robotino ip address>`
- To launch RViz visualization, use `ros2 launch rto_rviz_launch.py`
- **Note:** The robotino teleop package was not ported fully. To use keyboard teleop, run `sudo apt-get install ros-${ROS_DISTRO}-teleop-twist-keyboard` and then run `ros2 run teleop_twist_keyboard teleop_twist_keyboard`