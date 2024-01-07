/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RTOOdometryNode.h"


int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	RTOOdometryNode rn;
	rn.spin();
	return 0;
}
