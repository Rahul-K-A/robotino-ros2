/*
 * DigitalInputArrayROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef DIGITALINPUTARRAYROS_H_
#define DIGITALINPUTARRAYROS_H_

#include "rec/robotino/api2/DigitalInputArray.h"
#include "rclcpp/rclcpp.hpp"
#include "rto_msgs/msg/digital_readings.hpp"

class DigitalInputArrayROS: public rec::robotino::api2::DigitalInputArray
{
public:
	DigitalInputArrayROS(rclcpp::Node* parent_node);
	~DigitalInputArrayROS();

	void setTimeStamp(rclcpp::Time stamp);

private:
	rclcpp::Publisher<rto_msgs::msg::DigitalReadings>::SharedPtr digital_pub_;

	rto_msgs::msg::DigitalReadings digital_msg_;

	rclcpp::Time stamp_;

	void valuesChangedEvent( const int* values, unsigned int size );

};

#endif /* DIGITALINPUTARRAYROS_H_ */
