/*
 * LaserRangeFinderROS.h
 *
 *  Created on: 07.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef LASERRANGEFINDERROS_H_
#define LASERRANGEFINDERROS_H_

#include "rec/robotino/api2/LaserRangeFinder.h"
#include "rec/robotino/api2/LaserRangeFinderReadings.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

class LaserRangeFinderROS: public rec::robotino::api2::LaserRangeFinder
{
public:
	LaserRangeFinderROS();
	~LaserRangeFinderROS();

	void setNumber( int number, rclcpp::Node* parent_node );
	void setTimeStamp(rclcpp::Time stamp);

private:
	rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr laser_scan_pub_;

	sensor_msgs::msg::LaserScan laser_scan_msg_;

	rclcpp::Time stamp_;

	void scanEvent(const rec::robotino::api2::LaserRangeFinderReadings &scan);
};

#endif /* LASERRANGEFINDERROS_H_ */
