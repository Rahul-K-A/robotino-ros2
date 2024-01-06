/*
 * RTONode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RTOOdometryNode.h"

RTOOdometryNode::RTOOdometryNode()
	: nh_("~")
{
	nh_.param<std::string>("hostname", hostname_, "172.26.1.1" );

	com_.setName( "Odometry" );

	initModules();
}

RTOOdometryNode::~RTOOdometryNode()
{
}

void RTOOdometryNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	odometry_.setComId( com_.id() );

	com_.connectToServer( false );
}

bool RTOOdometryNode::spin()
{
	ros::Rate loop_rate( 30 );

	while(nh_.ok())
	{
		ros::Time curr_time = ros::Time::now();
		odometry_.setTimeStamp(curr_time);

		com_.processEvents();
		ros::spinOnce();
		loop_rate.sleep();
	}
	return true;
}

