/*
 * main.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "RTOCameraNode.h"

#include <ros/ros.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "rto_camera_node");
	RTOCameraNode rn;
	rn.spin();
	return 0;
}
