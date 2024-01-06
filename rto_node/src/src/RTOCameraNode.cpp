/*
 * RTONode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RTOCameraNode.h"
#include <sstream>

RTOCameraNode::RTOCameraNode()
	: nh_("~")
{
	nh_.param<std::string>("hostname", hostname_, "172.26.1.1" );
	nh_.param<int>("cameraNumber", cameraNumber_, 0 );

	std::ostringstream os;
	os << "Camera" << cameraNumber_;
	com_.setName( os.str() );

	initModules();
}

RTOCameraNode::~RTOCameraNode()
{
}

void RTOCameraNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	camera_.setComId( com_.id() );

	// Set the LaserRangeFinder numbers
	camera_.setNumber( cameraNumber_ );

	com_.connectToServer( false );
}

bool RTOCameraNode::spin()
{
	ros::Rate loop_rate( 30 );

	while(nh_.ok())
	{
		ros::Time curr_time = ros::Time::now();
		camera_.setTimeStamp(curr_time);

		com_.processEvents();
		ros::spinOnce();
		loop_rate.sleep();
	}
	return true;
}

