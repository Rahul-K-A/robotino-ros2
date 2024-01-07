/*
 * NorthStarROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "NorthStarROS.h"

#include "tf2/transform_datatypes.h"
#include "tf2/buffer_core.h"
#include "geometry_msgs/msg/quaternion.hpp"

NorthStarROS::NorthStarROS()
: parent_node(nullptr)
{
}



void NorthStarROS::setTimeStamp(rclcpp::Time stamp)
{
	stamp_ = stamp;
}

void NorthStarROS::setParentNode(rclcpp::Node::SharedPtr parent_node_ptr)
{
	assert(parent_node == nullptr);
	parent_node = parent_node_ptr;
	north_star_pub_ = parent_node->create_publisher<rto_msgs::msg::NorthStarReadings>("north_star", 10);

}

auto createQuaternionMsgFromYaw(double yaw)
{
  tf2::Quaternion q;
  q.setRPY(0, 0, yaw);
  return tf2::toMsg(q);
}


void NorthStarROS::readingsEvent( const rec::robotino::api2::NorthStarReadings& readings )
{
	geometry_msgs::msg::Quaternion quat = createQuaternionMsgFromYaw(readings.posTheta);

	// Build the NorthStarReadings msg
	north_star_msg_.stamp 				= stamp_;
	north_star_msg_.seq 				= readings.sequenceNumber;
	north_star_msg_.room_id 			= readings.roomId;
	north_star_msg_.num_spots_visible 	= readings.numSpotsVisible;
	north_star_msg_.pose.position.x 	= readings.posX;
	north_star_msg_.pose.position.y 	= readings.posY;
	north_star_msg_.pose.position.z 	= 0.0;
	north_star_msg_.pose.orientation	= quat;

	// Publish the message
	north_star_pub_->publish( north_star_msg_ );
}
