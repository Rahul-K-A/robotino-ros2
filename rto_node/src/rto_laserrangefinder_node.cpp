/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RTOLaserRangeFinderNode.h"

#include <ros/ros.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "rto_laserrangefinder_node");
	RTOLaserRangeFinderNode rn;
	rn.spin();
	return 0;
}
