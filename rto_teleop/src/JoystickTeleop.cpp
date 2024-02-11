/*
 * JoystickTeleop.cpp
 *
 *  Created on: 16.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "JoystickTeleop.h"

using std::placeholders::_1;
using namespace std::chrono_literals;

JoystickTeleop::JoystickTeleop(): Node("joystick_teleop_node")
{
	cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
	joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>("/joy",10, std::bind(&JoystickTeleop::joyCallback, this, _1));

	readParams();
	timer_ = this->create_wall_timer(200ms, std::bind(&JoystickTeleop::spin, this));

}

JoystickTeleop::~JoystickTeleop()
{
}

void JoystickTeleop::readParams()
{
	rclcpp::Parameter axis_linear_x_param_;
	rclcpp::Parameter axis_linear_y_param_;
	rclcpp::Parameter axis_angular_param_;
	rclcpp::Parameter scale_linear_param_;
	rclcpp::Parameter scale_angular_param_;
	rclcpp::Parameter scale_turbo_param_;
	rclcpp::Parameter deadzone_param_;

	this->get_parameter_or("axis_linear_x", axis_linear_x_param_, rclcpp::Parameter("axis_linear_x", 1));
	this->get_parameter_or("axis_linear_y", axis_linear_y_param_, rclcpp::Parameter("axis_linear_y", 0));
	this->get_parameter_or("axis_angular", axis_angular_param_, rclcpp::Parameter("axis_angular", 3));
	this->get_parameter_or("scale_linear", scale_linear_param_, rclcpp::Parameter("scale_linear", .03));
	this->get_parameter_or("scale_angular", scale_angular_param_, rclcpp::Parameter("scale_angular", .03));
	this->get_parameter_or("scale_turbo", scale_turbo_param_, rclcpp::Parameter("scale_turbo", .03));
	this->get_parameter_or("deadzone", deadzone_param_, rclcpp::Parameter("deadzone", .1));

	axis_linear_x_ = axis_linear_x_param_.as_int();
	axis_linear_y_ = axis_linear_y_param_.as_int();
	axis_angular_ = axis_angular_param_.as_int();
	scale_linear_ = scale_linear_param_.as_double();
	scale_angular_ = scale_angular_param_.as_double();
	scale_turbo_ = scale_turbo_param_.as_double();
	deadzone_ = deadzone_param_.as_double();
}

void JoystickTeleop::joyCallback( const sensor_msgs::msg::Joy::SharedPtr msg)
{
	if( msg->axes.size() < 3)
	{
		RCLCPP_ERROR(this->get_logger(), "Too few joystick axes: %lu (expected more than 3)", msg->axes.size());
		return;
	}

	auto axes = msg->axes;

	// Set turbo to 2 if button 'LB' is pressed, 1 otherwise
	float turbo = 1.0;
	if (msg->buttons[4] == 1)
		turbo = scale_turbo_;

	for (int i=0; i<axes.size(); i++)
	{
		if ( (axes[i] > 0 && axes[i] < deadzone_) ||
			 (axes[i] < 0 && axes[i] > -deadzone_) )
		{
			axes[i] = 0.0;
		}
	}

	// Use input only if button 'RB' is pressed otherwise set everything to zero 
	if (msg->buttons[5] == 1)
	{
		cmd_vel_msg_.linear.x = axes[axis_linear_x_] * scale_linear_ * turbo;
		cmd_vel_msg_.linear.y = axes[axis_linear_y_] * scale_linear_ * turbo;
		cmd_vel_msg_.angular.z = axes[axis_angular_] * scale_angular_ * turbo;
	}
	else
	{
		cmd_vel_msg_.linear.x = 0;
		cmd_vel_msg_.linear.y = 0;
		cmd_vel_msg_.angular.z = 0;
	}
}

void JoystickTeleop::spin()
{
	cmd_vel_pub_->publish( cmd_vel_msg_ );
}
