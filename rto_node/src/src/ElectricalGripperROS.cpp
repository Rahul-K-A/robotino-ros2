/*
 * ElectricalGripperROS.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "ElectricalGripperROS.h"

ElectricalGripperROS::ElectricalGripperROS()
{
	gripper_pub_ = nh_.advertise<rto_msgs::GripperState>("gripper_state", 1, true);
	set_gripper_server_ = nh_.advertiseService("set_gripper_state",
			&ElectricalGripperROS::setGripperStateCallback, this);
}

ElectricalGripperROS::~ElectricalGripperROS()
{
	gripper_pub_.shutdown();
	set_gripper_server_.shutdown();
}

void ElectricalGripperROS::setTimeStamp(ros::Time stamp)
{
	stamp_ = stamp;
}

bool ElectricalGripperROS::setGripperStateCallback(
		rto_msgs::SetGripperState::Request &req,
		rto_msgs::SetGripperState::Response &res)
{
	if( req.state )
		open();
	else
		close();

	return true;
}

void ElectricalGripperROS::stateChangedEvent( int state )
{
	// Build the GripperState msg
	gripper_msg_.stamp = stamp_;
	if( state == ElectricalGripper::IsOpen )
		gripper_msg_.state = true;
	else
		gripper_msg_.state = false;

	// Publish the msg
	gripper_pub_.publish( gripper_msg_ );
}
