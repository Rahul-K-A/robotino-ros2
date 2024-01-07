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
	timer_ = this->create_wall_timer(200ms,std::bind(&RTOOdometryNode::spin, this))
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

void RTOOdometryNode::spin()
{
	rclcpp::Time curr_time = rclcpp::Clock().now();
	odometry_.setTimeStamp(curr_time);

	com_.processEvents();
}

