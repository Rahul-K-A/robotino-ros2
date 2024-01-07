/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RTOCameraNode.h"

int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	RTOCameraNode rn;
	rn.spin();
	rclcpp::shutdown();
	return 0;
}
