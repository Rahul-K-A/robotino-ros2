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
	rclcpp::spin(std::make_shared<RTOOdometryNode>());
	return 0;
}
