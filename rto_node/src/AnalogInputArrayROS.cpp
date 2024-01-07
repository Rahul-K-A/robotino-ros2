/*
 * AnalogInputArrayROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "AnalogInputArrayROS.h"

AnalogInputArrayROS::AnalogInputArrayROS()
{
	analog_pub_ = this->create_publisher<rto_msgs::msg::AnalogReadings>("analog_readings", 10);
	analog_msg_ = rto_msgs::msg::AnalogReadings();
}

AnalogInputArrayROS::~AnalogInputArrayROS()
{
}

void AnalogInputArrayROS::setTimeStamp(rclcpp::Time stamp)
{
	stamp_ = stamp;
}

void AnalogInputArrayROS::valuesChangedEvent( const float* values, unsigned int size )
{
	// Build the AnalogReadings msg
	analog_msg_.stamp = stamp_;
	analog_msg_.values.resize(size);

	if( size > 0 )
	{
		memcpy( analog_msg_.values.data(), values, size * sizeof( float ) );

		// Publish the msg
		analog_pub_->publish(analog_msg_);
	}
}
