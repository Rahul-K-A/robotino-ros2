/*
 * PowerManagementROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "PowerManagementROS.h"

PowerManagementROS::PowerManagementROS():
parent_node(nullptr)
{
}

PowerManagementROS::~PowerManagementROS()
{
}

void PowerManagementROS::setParentNode(const rclcpp::Node::SharedPtr parent_node_ptr)
{
	assert(parent_node == nullptr);
	parent_node = parent_node_ptr;
	power_pub_ = parent_node->create_publisher<rto_msgs::msg::PowerReadings>("power_readings", 10);
}

void PowerManagementROS::setTimeStamp(rclcpp::Time stamp)
{
	stamp_ = stamp;
}

void PowerManagementROS::readingsEvent(float current, float voltage)
{
	// Build the PowerReadings msg
	power_msg_.stamp = rclcpp::Clock().now();
	power_msg_.current = current;
	power_msg_.voltage = voltage;

	// Publish the msg
	power_pub_->publish( power_msg_ );
}
