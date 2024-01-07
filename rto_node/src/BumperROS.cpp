/*
 * BumperROS.cpp
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */


#include "rto_node/BumperROS.h"

BumperROS::BumperROS()
{

	//bumper_pub_ = this->create_publisher<std_msgs::msg::Bool>("bumper", 10);
	bumper_msg_ = std_msgs::msg::Bool();

}

void BumperROS::setParentNode(const rclcpp::Node::SharedPtr parent_node_ptr)
{
	parent_node = parent_node_ptr;
}

BumperROS::~BumperROS()
{
}

void BumperROS::bumperEvent(bool hasContact)
{
	bumper_msg_.data = hasContact;
	bumper_pub_->publish(bumper_msg_);
}
