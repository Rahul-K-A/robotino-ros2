/*
 * DigitalOutputArrayROS.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "DigitalOutputArrayROS.h"

using std::placeholders::_1;
DigitalOutputArrayROS::DigitalOutputArrayROS(rclcpp::Node * parent_node)
{
	digital_sub_ = parent_node->create_subscription<rto_msgs::msg::DigitalReadings>("set_digital_values", 10, std::bind(&DigitalOutputArrayROS::setDigitalValuesCallback, this, _1));
}

DigitalOutputArrayROS::~DigitalOutputArrayROS()
{
}

void DigitalOutputArrayROS::setDigitalValuesCallback( const rto_msgs::msg::DigitalReadings::SharedPtr msg)
{
	int numValues = msg->values.size();
	if( numValues > 0 )
	{
		int values[numValues];

		for(uint8_t entry = 0; entry < numValues; entry++)
		{
			values[entry] = msg->values[entry];
		}
		setValues( values, numValues );
	}
}
