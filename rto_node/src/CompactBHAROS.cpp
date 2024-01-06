/*
 * CompactBHAROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "CompactBHAROS.h"

CompactBHAROS::CompactBHAROS()
{
	bha_pub_ = nh_.advertise<rto_msgs::BHAReadings>("bha_readings", 1, true);
	bha_sub_ = nh_.subscribe("set_bha_pressures", 1, &CompactBHAROS::setBHAPressuresCallback, this);
}

CompactBHAROS::~CompactBHAROS()
{
	bha_pub_.shutdown();
	bha_sub_.shutdown();
}

void CompactBHAROS::setTimeStamp(ros::Time stamp)
{
	stamp_ = stamp;
}

void CompactBHAROS::pressuresChangedEvent( const float* pressures, unsigned int size )
{
	// Build the BHAReadings msg
	bha_msg_.pressures.resize( size, 0.0 );

	if( pressures != NULL )
	{
		memcpy( bha_msg_.pressures.data(), pressures, size * sizeof(float) );
	}
}

void CompactBHAROS::cablepullChangedEvent( const float* cablepull, unsigned int size )
{
	// Build the BHAReadings msg
	bha_msg_.cablepull.resize( size, 0.0 );
	if( cablepull != NULL )
	{
		memcpy( bha_msg_.cablepull.data(), cablepull, size * sizeof(float) );
	}

	// Publish the msg
	bha_pub_.publish( bha_msg_ );
}

void CompactBHAROS::setBHAPressuresCallback(const rto_msgs::SetBHAPressuresConstPtr &msg)
{
	float pressures[8];

	if( msg->pressures.size() == 8 )
	{
		for(int i = 0; i < 8; ++i)
		{
			pressures[i] = msg->pressures[i];
		}

		setPressures( pressures );
	}
}
