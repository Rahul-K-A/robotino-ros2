/*
 * ElectricalGripperROS.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ELECTRICALGRIPPERROS_H_
#define ELECTRICALGRIPPERROS_H_

#include "rec/robotino/api2/ElectricalGripper.h"

#include <ros/ros.h>
#include "rto_msgs/GripperState.h"
#include "rto_msgs/SetGripperState.h"


class ElectricalGripperROS : public rec::robotino::api2::ElectricalGripper
{
public:
	ElectricalGripperROS();
	~ElectricalGripperROS();

	void setTimeStamp(ros::Time stamp);

private:
	ros::NodeHandle nh_;

	ros::Publisher gripper_pub_;

	ros::ServiceServer set_gripper_server_;

	rto_msgs::GripperState gripper_msg_;

	ros::Time stamp_;

	bool setGripperStateCallback(
			rto_msgs::SetGripperState::Request &req,
			rto_msgs::SetGripperState::Response &res);

	void stateChangedEvent( int state );

};

#endif /* ELECTRICALGRIPPERROS_H_ */
