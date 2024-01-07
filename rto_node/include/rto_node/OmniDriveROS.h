/*
 * OmniDriveROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef OMNIDRIVEROS_H_
#define OMNIDRIVEROS_H_

#include "rec/robotino/api2/OmniDrive.h"

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

class OmniDriveROS: public rec::robotino::api2::OmniDrive
{
public:
	OmniDriveROS();
	~OmniDriveROS();

	void setParentNode(const rclcpp::Node::SharedPtr parent_node_ptr);

private:
	rclcpp::Node::SharedPtr parent_node;
	rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;

	double max_linear_vel_;
	double min_linear_vel_;
	double max_angular_vel_;
	double min_angular_vel_;

	void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);

public:
	void setMaxMin( double max_linear_vel, double min_linear_vel,
				double max_angular_vel, double min_angular_vel );
};

#endif /* OMNIDRIVEROS_H_ */
