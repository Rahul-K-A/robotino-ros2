/*
 * OdometryROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ODOMETRYROS_H_
#define ODOMETRYROS_H_

#include "rec/robotino/api2/Odometry.h"
#include "rto_msgs/srv/reset_odometry.hpp"

#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"

#include "nav_msgs/msg/odometry.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

class OdometryROS: public rec::robotino::api2::Odometry
{
public:
	OdometryROS(rclcpp::Node* parent_node);
	~OdometryROS();

	void setTimeStamp(rclcpp::Time stamp);

private:
	rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odometry_pub_;

	rclcpp::Service<rto_msgs::srv::ResetOdometry>::SharedPtr reset_odometry_server_;

	nav_msgs::msg::Odometry odometry_msg_;
	geometry_msgs::msg::TransformStamped odometry_transform_;

	tf2_ros::TransformBroadcaster odometry_transform_broadcaster_;

	rclcpp::Time stamp_;


	void readingsEvent(double x, double y, double phi,
			float vx, float vy, float omega, unsigned int sequence );
	bool resetOdometryCallback(
			rto_msgs::srv::ResetOdometry::Request::SharedPtr req,
			rto_msgs::srv::ResetOdometry::Response::SharedPtr res);
};

#endif /* ODOMETRYROS_H_ */
