/*
 * MotorArrayROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef MOTORARRAYROS_H_
#define MOTORARRAYROS_H_

#include "rec/robotino/api2/MotorArray.h"
#include "rclcpp/rclcpp.hpp"
#include "rto_msgs/msg/motor_readings.h"

class MotorArrayROS : public rec::robotino::api2::MotorArray
{
public:
	MotorArrayROS();
	~MotorArrayROS();

	void setTimeStamp(rclcpp::Time stamp);
	void getMotorReadings(std::vector<float> &velocities, std::vector<int> &positions );
	void setParentNode(const rclcpp::Node::SharedPtr parent_node_ptr);

private:
	rclcpp::Node::SharedPtr parent_node;
	rclcpp::Publisher<rto_msgs::msg::MotorReadings> motor_pub_;

	rto_msgs::msg::MotorReadings motor_msg_;

	rclcpp::Time stamp_;

	void velocitiesChangedEvent( const float* velocities, unsigned int size );
	void positionsChangedEvent( const float* positions, unsigned int size );
	void currentsChangedEvent( const float* currents, unsigned int size );
};
#endif /* MOTORARRAYROS_H_ */
