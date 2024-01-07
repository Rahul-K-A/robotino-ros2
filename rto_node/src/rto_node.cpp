/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */



#include "RTONode.h"


int main(int argc, char** argv)
{
	rclcpp::init(argc, argv, "rto_node");
	RTONode rn;
	rn.spin();
	return 0;
}
