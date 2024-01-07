/*
 * RTONode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RTOOdometryNode.h"

using namespace std::chrono_literals;

RTOOdometryNode::RTOOdometryNode():
Node( "rto_odometry_node")
{
	rclcpp::Parameter hostname_param_;
	rclcpp::Parameter laser_range_finder_number_param_;
	this->get_parameter_or("hostname", hostname_param_, rclcpp::Parameter("hostname", "172.26.1.1") );
	hostname_ = hostname_param_.as_string();
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
	rclcpp::WallRate loop_rate( 200ms );

	while(rclcpp::ok())
	{
		rclcpp::Time curr_time = rclcpp::Clock().now();
		odometry_.setTimeStamp(curr_time);

		com_.processEvents();
		rclcpp::spin_some(shared_from_this());
		loop_rate.sleep();
	}
	return true;
}

