/*
 * DigitalOutputArrayROS.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef DIGITALOUTPUTARRAYROS_H_
#define DIGITALOUTPUTARRAYROS_H_

#include "rec/robotino/api2/DigitalOutputArray.h"
#include "rclcpp/rclcpp.hpp"
#include "rto_msgs/msg/digital_readings.hpp"

class DigitalOutputArrayROS: public rec::robotino::api2::DigitalOutputArray
{
public:
	DigitalOutputArrayROS(rclcpp::Node* parent_node);
	~DigitalOutputArrayROS();

private:

	rclcpp::Subscription<rto_msgs::msg::DigitalReadings>::SharedPtr digital_sub_;

	void setDigitalValuesCallback( const rto_msgs::msg::DigitalReadings::SharedPtr msg);

};

#endif /* DIGITALOUTPUTARRAYROS_H_ */
