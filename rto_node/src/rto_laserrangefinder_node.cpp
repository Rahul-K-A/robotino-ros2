/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RTOLaserRangeFinderNode.h"


int main(int argc, char** argv)
{
	rclcpp::init(argc, argv);
	RTOLaserRangeFinderNode rn;
	rn.spin();
	return 0;
}
