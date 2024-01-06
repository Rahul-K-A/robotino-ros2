/*
 * NorthStarROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef NORTHSTARROS_H_
#define NORTHSTARROS_H_

#include "rec/robotino/api2/NorthStar.h"

#include <ros/ros.h>
#include "rto_msgs/NorthStarReadings.h"

class NorthStarROS : public rec::robotino::api2::NorthStar
{
public:
	NorthStarROS();
	~NorthStarROS();

	void setTimeStamp(ros::Time stamp);

private:
	ros::NodeHandle nh_;

	ros::Publisher north_star_pub_;

	rto_msgs::NorthStarReadings north_star_msg_;

	ros::Time stamp_;

	void readingsEvent( const rec::robotino::api2::NorthStarReadings& readings );
};

#endif /* NORTHSTARROS_H_ */
