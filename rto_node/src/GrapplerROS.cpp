/*
 * GrapplerROS.cpp
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "GrapplerROS.h"

GrapplerROS::GrapplerROS()
{
	grappler_readings_pub_ = nh_.advertise<rto_msgs::GrapplerReadings>("grappler_readings", 1, true);
	grappler_store_pub_ = nh_.advertise<rto_msgs::GrapplerReadings>("grappler_store_positions", 1, false);
	grappler_axes_sub_ = nh_.subscribe("set_grappler_axes", 1, &GrapplerROS::setGrapplerAxes, this);
	grappler_axis_sub_ = nh_.subscribe("set_grappler_axis", 1, &GrapplerROS::setGrapplerAxis, this);
}

GrapplerROS::~GrapplerROS()
{
	grappler_readings_pub_.shutdown();
	grappler_store_pub_.shutdown();
	grappler_axes_sub_.shutdown();
	grappler_axis_sub_.shutdown();
}

void GrapplerROS::setTimeStamp(ros::Time stamp)
{
	stamp_ = stamp;
}

void GrapplerROS::readingsEvent( const rec::robotino::api2::GrapplerReadings& readings )
{
	unsigned int numServos = readings.numServos;

	// Build the GrapplerReadings msg
	grappler_readings_msg_.stamp 		= stamp_;
	grappler_readings_msg_.seq 			= readings.sequenceNumber;
	grappler_readings_msg_.numServos 	= numServos;
	grappler_readings_msg_.torqueEnabled = readings.isTorqueEnabled;

	grappler_readings_msg_.angles.resize( numServos );
	grappler_readings_msg_.errors.resize( numServos );
	grappler_readings_msg_.channels.resize( numServos );
	grappler_readings_msg_.ids.resize( numServos );
	grappler_readings_msg_.cwAxesLimits.resize( numServos );
	grappler_readings_msg_.ccwAxesLimits.resize( numServos );

	for( unsigned int i = 0; i < numServos; ++i)
	{
		grappler_readings_msg_.angles[i] 		= readings.angles[i];
		grappler_readings_msg_.errors[i] 		= readings.errors[i];
		grappler_readings_msg_.channels[i] 		= readings.channels[i];
		grappler_readings_msg_.ids[i] 			= readings.ids[i];
		grappler_readings_msg_.cwAxesLimits[i] 	= readings.cwAxesLimits[i];
		grappler_readings_msg_.ccwAxesLimits[i] = readings.ccwAxesLimits[i];
	}

	// Publish the msg
	grappler_readings_pub_.publish( grappler_readings_msg_ );
}

void GrapplerROS::storePositionsEvent( const rec::robotino::api2::GrapplerReadings& readings )
{
	unsigned int numServos = readings.numServos;

	// Build the GrapplerReadings msg
	grappler_store_msg_.stamp 		= stamp_;
	grappler_store_msg_.seq 			= readings.sequenceNumber;
	grappler_store_msg_.numServos 	= numServos;
	grappler_store_msg_.torqueEnabled = readings.isTorqueEnabled;

	grappler_store_msg_.angles.resize( numServos );
	grappler_store_msg_.errors.resize( numServos );
	grappler_store_msg_.channels.resize( numServos );
	grappler_store_msg_.ids.resize( numServos );
	grappler_store_msg_.cwAxesLimits.resize( numServos );
	grappler_store_msg_.ccwAxesLimits.resize( numServos );

	for( unsigned int i = 0; i < numServos; ++i)
	{
		grappler_store_msg_.angles[i] 		= readings.angles[i];
		grappler_store_msg_.errors[i] 		= readings.errors[i];
		grappler_store_msg_.channels[i] 		= readings.channels[i];
		grappler_store_msg_.ids[i] 			= readings.ids[i];
		grappler_store_msg_.cwAxesLimits[i] 	= readings.cwAxesLimits[i];
		grappler_store_msg_.ccwAxesLimits[i] 	= readings.ccwAxesLimits[i];
	}

	// Publish the msg
	grappler_store_pub_.publish( grappler_store_msg_ );
}

void GrapplerROS::setGrapplerAxes( const rto_msgs::SetGrapplerAxesConstPtr& msg)
{
	int numAngles = msg->angles.size();
	int numVelocities = msg->velocities.size();
	if( numAngles == numVelocities && numAngles > 0 )
	{
		float angles[numAngles];
		float velocities[numVelocities];

		memcpy(angles, msg->angles.data(), numAngles * sizeof(float) );
		memcpy(velocities, msg->velocities.data(), numVelocities * sizeof(float) );

		setAxes( angles, numAngles, velocities, numVelocities);
	}
}

void GrapplerROS::setGrapplerAxis( const rto_msgs::SetGrapplerAxisConstPtr& msg)
{
	int axis = msg->axis;
	int angle = msg->angle;
	int velocity = msg->velocity;
	setAxis( axis, angle, velocity );
}
