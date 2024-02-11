/*
 * ComROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "ComROS.h"
#include <sstream>

ComROS::ComROS(rclcpp::Node* parent_node_ptr)
{
	parent_node_name_ = std::string(parent_node_ptr->get_name());
}

ComROS::~ComROS()
{
}

void ComROS::setName( const std::string& name )
{
	name_ = name;
}

void ComROS::errorEvent( const char* errorString )
{
	std::ostringstream os;
	os << name_ << " : " << errorString;

	RCLCPP_ERROR(rclcpp::get_logger(parent_node_name_), "%s", os.str().c_str() );
}

void ComROS::connectedEvent()
{
	std::ostringstream os;
	os << name_ << " connected to RTO.";
	RCLCPP_INFO(rclcpp::get_logger(parent_node_name_), "%s", os.str().c_str());
}

void ComROS::connectionClosedEvent()
{
	std::ostringstream os;
	os << name_ << " disconnected from RTO.";
	RCLCPP_INFO(rclcpp::get_logger(parent_node_name_), "%s", os.str().c_str());
}
