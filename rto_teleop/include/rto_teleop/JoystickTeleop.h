/*
 * JoystickTeleop.h
 *
 *  Created on: 16.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef JOYSTICKTELEOP_H_
#define JOYSTICKTELEOP_H_

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joy.hpp"

class JoystickTeleop : public rclcpp::Node
{
public:
	JoystickTeleop();
	~JoystickTeleop();

private:

	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;

	geometry_msgs::msg::Twist cmd_vel_msg_;

	void readParams();
	void joyCallback( const sensor_msgs::msg::Joy::SharedPtr msg);

	// params
	int axis_linear_x_;
	int axis_linear_y_;
	int axis_angular_;
	double scale_linear_;
	double scale_angular_;
	double scale_turbo_;
	double deadzone_;

public:
	rclcpp::TimerBase::SharedPtr timer_;
	void spin();
};


#endif /* JOYSTICKTELEOP_H_ */
