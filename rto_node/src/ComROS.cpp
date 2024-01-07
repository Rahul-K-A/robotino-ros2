/*
 * ComROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "ComROS.h"
#include <sstream>

ComROS::ComROS()
{
}

ComROS::~ComROS()
{
}

void ComROS::setName( const std::string& name )
{
	name_ = name;
}

void ComROS::setParentNode(const rclcpp::Node::SharedPtr parent_node_ptr)
{
	parent_node = parent_node_ptr;
}

void ComROS::errorEvent( const char* errorString )
{
	std::ostringstream os;
	os << name_ << " : " << errorString;

	RCLCPP_ERROR(parent_node->get_logger(), "%s", os.str().c_str() );
}

void ComROS::connectedEvent()
{
	std::ostringstream os;
	os << name_ << " connected to RTO.";
	RCLCPP_INFO(parent_node->get_logger(), "%s", os.str().c_str());
}

void ComROS::connectionClosedEvent()
{
	std::ostringstream os;
	os << name_ << " disconnected from RTO.";
	RCLCPP_INFO(parent_node->get_logger(), "%s", os.str().c_str());
}
