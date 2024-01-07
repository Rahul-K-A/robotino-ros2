/*
 * RTONode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RTOCameraNode.h"
#include <sstream>

using namespace std::chrono_literals;

RTOCameraNode::RTOCameraNode():
	Node("rto_camera_node"),
	com_(this)
{
	rclcpp::Parameter hostname_param_;
	rclcpp::Parameter camera_param_;
	this->get_parameter_or("hostname", hostname_param_, rclcpp::Parameter("hostname", "172.26.1.1") );
	this->get_parameter_or("cameraNumber", camera_param_, rclcpp::Parameter("cameraNumber", 0));
	hostname_ = hostname_param_.as_string();
	cameraNumber_ = camera_param_.as_int();
	std::ostringstream os;
	os << "Camera" << cameraNumber_;
	com_.setName( os.str() );

	initModules();
	timer_ = this->create_wall_timer(200ms, std::bind(&RTOCameraNode::spin, this));
}

RTOCameraNode::~RTOCameraNode()
{
}

void RTOCameraNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	camera_.setComId( com_.id() );

	// Set the camera numbers
	camera_.setNumber( cameraNumber_ , this);

	com_.connectToServer( false );
}

void RTOCameraNode::spin()
{
	rclcpp::Time curr_time = rclcpp::Clock().now();
	camera_.setTimeStamp(curr_time);

	com_.processEvents();
	rclcpp::spin_some(shared_from_this());
}

