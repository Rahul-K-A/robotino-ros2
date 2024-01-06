/*
 * RTONode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ROBOTINONODE_H_
#define ROBOTINONODE_H_

#include "AnalogInputArrayROS.h"
#include "BumperROS.h"
#include "CompactBHAROS.h"
#include "ComROS.h"
#include "DigitalInputArrayROS.h"
#include "DigitalOutputArrayROS.h"
#include "DistanceSensorArrayROS.h"
#include "ElectricalGripperROS.h"
#include "EncoderInputROS.h"
#include "GrapplerROS.h"
#include "MotorArrayROS.h"
#include "NorthStarROS.h"
#include "OmniDriveROS.h"
#include "PowerManagementROS.h"

#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/JointState.h>


class RTONode
{
public:
	RTONode();
	~RTONode();

private:
	ros::NodeHandle nh_;

	std::string hostname_;
	double max_linear_vel_, min_linear_vel_, max_angular_vel_, min_angular_vel_;
	std::vector<float> motor_velocities_;
	std::vector<int> motor_positions_;

	ros::Time curr_time_, clearing_time_;

	ros::Publisher distances_clearing_pub_;
	ros::Publisher joint_states_pub_;

	sensor_msgs::PointCloud distances_clearing_msg_;
	sensor_msgs::JointState joint_state_msg_;

	AnalogInputArrayROS analog_input_array_;
	BumperROS bumper_;
	CompactBHAROS compact_bha_;
	ComROS com_;
	DigitalInputArrayROS digital_input_array_;
	DigitalOutputArrayROS digital_output_array_;
	DistanceSensorArrayROS distance_sensor_array_;
	ElectricalGripperROS electrical_gripper_;
	EncoderInputROS encoder_input_;
	GrapplerROS grappler_;
	MotorArrayROS motor_array_;
	//NorthStarROS north_star_;
	OmniDriveROS omni_drive_;
	PowerManagementROS power_management_;

	void initModules();
	void initMsgs();
	void publishDistanceMsg();
	void publishJointStateMsg();

public:
	bool spin();
};

#endif /* ROBOTINONODE_H_ */
