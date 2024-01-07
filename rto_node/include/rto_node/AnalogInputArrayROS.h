/*
 * AnalogInputArrayROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ANALOGINPUTARRAYROS_H_
#define ANALOGINPUTARRAYROS_H_

#include "rec/robotino/api2/AnalogInputArray.h"
#include "rclcpp/rclcpp.hpp"
#include "rto_msgs/msg/analog_readings.hpp"

class AnalogInputArrayROS: public rec::robotino::api2::AnalogInputArray, public rclcpp::Node
{
public:
	AnalogInputArrayROS();
	~AnalogInputArrayROS();

	void setTimeStamp(rclcpp::Time stamp);

private:
	rclcpp::Publisher<rto_msgs::msg::AnalogReadings>::SharedPtr analog_pub_;

	rto_msgs::msg::AnalogReadings analog_msg_;

	rclcpp::Time stamp_;

	void valuesChangedEvent( const float* values, unsigned int size );

};


#endif /* ANALOGINPUTARRAYROS_H_ */
