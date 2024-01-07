/*
 * DigitalInputArrayROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "DigitalInputArrayROS.h"

DigitalInputArrayROS::DigitalInputArrayROS(rclcpp::Node* parent_node)
{
	digital_pub_ = parent_node->create_publisher<rto_msgs::msg::DigitalReadings>("digital_readings", 10);
	digital_msg_ = rto_msgs::msg::DigitalReadings();
}

DigitalInputArrayROS::~DigitalInputArrayROS()
{
}

void DigitalInputArrayROS::setTimeStamp(rclcpp::Time stamp)
{
	stamp_ = stamp;
}

void DigitalInputArrayROS::valuesChangedEvent( const int* values, unsigned int size )
{
	// Build the DigitalReadings msg
	digital_msg_.stamp = stamp_;
	digital_msg_.values.resize( size );

	if( size > 0 )
	{
        for( unsigned int idx = 0; idx < size; ++idx )
        {
            digital_msg_.values[idx] = (bool)values[idx];
        }
		// Publish the msg
		digital_pub_->publish( digital_msg_ );
	}

}
