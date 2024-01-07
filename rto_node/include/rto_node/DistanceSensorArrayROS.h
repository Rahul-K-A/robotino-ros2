/*
 * DistanceSensorArrayROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef DISTANCESENSORARRAYROS_H_
#define DISTANCESENSORARRAYROS_H_

#include "rec/robotino/api2/DistanceSensorArray.h"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud.hpp"

class DistanceSensorArrayROS: public rec::robotino::api2::DistanceSensorArray
{
public:
	DistanceSensorArrayROS();
	~DistanceSensorArrayROS();

	void setTimeStamp(rclcpp::Time stamp);

private:

	rclcpp::Publisher<sensor_msgs::msg::PointCloud>::SharedPtr distances_pub_;

	sensor_msgs::msg::PointCloud distances_msg_;

	rclcpp::Time stamp_;

	void distancesChangedEvent(const float* distances, unsigned int size);

};


#endif /* DISTANCESENSORARRAYROS_H_ */
