/*
 * RTONode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ROBOTINOLaserRangeFinderNODE_H_
#define ROBOTINOLaserRangeFinderNODE_H_

#include "ComROS.h"
#include "LaserRangeFinderROS.h"

#include "rclcpp/rclcpp.hpp"

class RTOLaserRangeFinderNode : public rclcpp::Node
{
public:
	RTOLaserRangeFinderNode();
	~RTOLaserRangeFinderNode();


private:
	rclcpp::TimerBase::SharedPtr timer_;
	std::string hostname_;
	int laserRangeFinderNumber_;

	ComROS com_;
	LaserRangeFinderROS laser_range_finder_;
	void spin();
	void initModules();
};

#endif /* ROBOTINOLaserRangeFinderNODE_H_ */
