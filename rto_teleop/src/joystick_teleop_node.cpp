/*
 * joystick_teleop_node.cpp
 *
 *  Created on: 16.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "JoystickTeleop.h"

int main( int argc, char** argv )
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<JoystickTeleop>());
	return 0;
}

