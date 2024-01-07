/*
 * NorthStarROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef NORTHSTARROS_H_
#define NORTHSTARROS_H_

#include "rec/robotino/api2/NorthStar.h"

#include "rclcpp/rclcpp.hpp"
#include "rto_msgs/msg/north_star_readings.hpp"

class NorthStarROS : public rec::robotino::api2::NorthStar
{
public:
	NorthStarROS();
	~NorthStarROS();

	void setTimeStamp(rclcpp::Time stamp);
	void setParentNode(rclcpp::Node::SharedPtr parent_node_ptr );

private:
	rclcpp::Node::SharedPtr parent_node;
	rclcpp::Publisher<rto_msgs::msg::NorthStarReadings>::SharedPtr north_star_pub_;

	rto_msgs::msg::NorthStarReadings north_star_msg_;

	rclcpp::Time stamp_;

	void readingsEvent( const rec::robotino::api2::NorthStarReadings& readings );
};

#endif /* NORTHSTARROS_H_ */
