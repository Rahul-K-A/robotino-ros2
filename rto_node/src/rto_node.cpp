/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include <sensor_msgs/fill_image.h>

#include "RTONode.h"

#include <ros/ros.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "rto_node");
	RTONode rn;
	rn.spin();
	return 0;
}
