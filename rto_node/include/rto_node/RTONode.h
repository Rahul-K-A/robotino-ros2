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
#include "ComROS.h"
#include "DigitalInputArrayROS.h"
#include "DigitalOutputArrayROS.h"
#include "DistanceSensorArrayROS.h"
#include "EncoderInputROS.h"
#include "MotorArrayROS.h"
#include "OmniDriveROS.h"
#include "PowerManagementROS.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud.hpp"
#include "sensor_msgs/msg/joint_state.hpp"


class RTONode : public rclcpp::Node
{
public:
	RTONode();
	~RTONode();

private:
	std::string hostname_;
	double max_linear_vel_, min_linear_vel_, max_angular_vel_, min_angular_vel_;
	std::vector<float> motor_velocities_;
	std::vector<int> motor_positions_;

	rclcpp::Time curr_time_, clearing_time_;

	rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr distances_clearing_pub_;
	rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_states_pub_;

	sensor_msgs::msg::PointCloud distances_clearing_msg_;
	sensor_msgs::msg::JointState joint_state_msg_;

	AnalogInputArrayROS analog_input_array_;
	BumperROS bumper_;
	ComROS com_;
	DigitalInputArrayROS digital_input_array_;
	DigitalOutputArrayROS digital_output_array_;
	DistanceSensorArrayROS distance_sensor_array_;
	EncoderInputROS encoder_input_;
	MotorArrayROS motor_array_;
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
