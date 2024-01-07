/*
 * RTONode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RTONode.h"

using namespace std::chrono_literals;

RTONode::RTONode():
	Node("rto_node"),
	analog_input_array_(this),
	bumper_(this),
	com_(),
	digital_input_array_(this),
	digital_output_array_(this),
	distance_sensor_array_(this),
	encoder_input_(this),
	motor_array_(this),
	omni_drive_(this),
	power_management_(this)
{
	rclcpp::Parameter hostname_param_;
	rclcpp::Parameter max_lin_vel_param_;
	rclcpp::Parameter min_lin_vel_param_;
	rclcpp::Parameter max_ang_vel_param_;
	rclcpp::Parameter min_ang_vel_param_;
	this->get_parameter_or("hostname", hostname_param_, rclcpp::Parameter("hostname", "172.26.1.1"));
	this->get_parameter_or("max_linear_vel", max_lin_vel_param_, rclcpp::Parameter("max_linear_vel", 0.2));
	this->get_parameter_or("min_linear_vel", min_lin_vel_param_, rclcpp::Parameter("min_linear_vel", 0.05));
	this->get_parameter_or("max_angular_vel", max_ang_vel_param_, rclcpp::Parameter("max_angular_vel", 1.0));
	this->get_parameter_or("min_angular_vel", min_ang_vel_param_, rclcpp::Parameter("min_angular_vel", 0.1));

	hostname_ = hostname_param_.as_string();
	max_linear_vel_ = max_lin_vel_param_.as_double();
	min_linear_vel_ = min_lin_vel_param_.as_double();
	max_angular_vel_ = max_ang_vel_param_.as_double();
	min_angular_vel_ = min_ang_vel_param_.as_double();

	distances_clearing_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud>("/distance_sensors_clearing", 10);
	joint_states_pub_= this->create_publisher<sensor_msgs::msg::JointState>("/rto_joint_states", 10);

	com_.setName( "RTONode" );

	initModules();
	initMsgs();
	timer_ = this->create_wall_timer(200ms, std::bind(&RTONode::spin, this));
}

RTONode::~RTONode()
{
}

void RTONode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	analog_input_array_.setComId( com_.id() );
	bumper_.setComId( com_.id() );
	digital_input_array_.setComId( com_.id() );
	digital_output_array_.setComId( com_.id() );
	distance_sensor_array_.setComId( com_.id() );
	encoder_input_.setComId( com_.id() );
	motor_array_.setComId( com_.id() );
	omni_drive_.setComId( com_.id() );
	power_management_.setComId( com_.id() );
	omni_drive_.setMaxMin(max_linear_vel_, min_linear_vel_, max_angular_vel_, min_angular_vel_ );
	com_.connectToServer( false );
}

void RTONode::initMsgs()
{
	distances_clearing_msg_.header.frame_id = "base_link";
	distances_clearing_msg_.header.stamp = curr_time_;
	distances_clearing_msg_.points.resize( 720 );

	for( unsigned int i = 0; i < distances_clearing_msg_.points.size(); ++i )
	{
		distances_clearing_msg_.points[i].x = 5.0 * cos(  0.008727 ); // 0.008727 = 0.5 degrees in radians
		distances_clearing_msg_.points[i].y = 5.0 * sin(  0.008727 );
		distances_clearing_msg_.points[i].z = 0.05; // 5cm above ground
	}

	joint_state_msg_.name.resize(3);
	joint_state_msg_.position.resize(3, 0.0);
	joint_state_msg_.velocity.resize(3, 0.0);
	joint_state_msg_.name[0] = "wheel2_joint";
	joint_state_msg_.name[1] = "wheel0_joint";
	joint_state_msg_.name[2] = "wheel1_joint";

	motor_velocities_.resize(4);
	motor_positions_.resize(4);
}

void RTONode::publishDistanceMsg()
{
//	curr_time_ = ros::Time::now();
//	if( ( curr_time_ - clearing_time_ ).toSec() > 1 )
//	{
//		clearing_time_ = curr_time_;
//		distances_clearing_pub_.publish( distances_clearing_msg_ );
//	}
	distances_clearing_pub_->publish( distances_clearing_msg_ );
}

void RTONode::publishJointStateMsg()
{
	motor_array_.getMotorReadings( motor_velocities_, motor_positions_ );

	joint_state_msg_.velocity[0] = ( ( motor_velocities_[2] / 16 ) * (2 * 3.142) / 60 );
	joint_state_msg_.velocity[1] = ( ( motor_velocities_[0] / 16 ) * (2 * 3.142) / 60 );
	joint_state_msg_.velocity[2] = ( ( motor_velocities_[1] / 16 ) * (2 * 3.142) / 60 );

	joint_state_msg_.position[0] = ( motor_positions_[2] / 16 ) * (2 * 3.142);
	joint_state_msg_.position[1] = ( motor_positions_[0] / 16 ) * (2 * 3.142);
	joint_state_msg_.position[2] = ( motor_positions_[1] / 16 ) * (2 * 3.142);

	joint_state_msg_.header.stamp = curr_time_;
	joint_states_pub_->publish( joint_state_msg_ );
}

void RTONode::spin()
{
	curr_time_ = rclcpp::Clock().now();
	RCLCPP_INFO(this->get_logger(),"7.1");
	analog_input_array_.setTimeStamp(curr_time_);
	RCLCPP_INFO(this->get_logger(),"7.2");
	digital_input_array_.setTimeStamp(curr_time_);
	distance_sensor_array_.setTimeStamp(curr_time_);
	encoder_input_.setTimeStamp(curr_time_);
	motor_array_.setTimeStamp(curr_time_);
	//north_star_.setTimeStamp(curr_time_);
	power_management_.setTimeStamp(curr_time_);

	publishDistanceMsg();
	publishJointStateMsg();
	com_.processEvents();
}

