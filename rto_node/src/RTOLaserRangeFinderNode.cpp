/*
 * RTONode.cpp
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#include "RTOLaserRangeFinderNode.h"
#include <sstream>
using namespace std::chrono_literals;

RTOLaserRangeFinderNode::RTOLaserRangeFinderNode():
	Node("rto_laserrangefinder_node"),
	com_(this)
{
	this->declare_parameter("hostname", "172.26.1.1");
	this->declare_parameter("laserRangeFinderNumber", 0);
	hostname_ = this->get_parameter("hostname").as_string();
	laserRangeFinderNumber_ = this->get_parameter("laserRangeFinderNumber").as_int();
	std::ostringstream os;
	os << "LaserRangeFinder" << laserRangeFinderNumber_;
	com_.setName( os.str() );

	initModules();
	timer_ = this->create_wall_timer(200ms, std::bind(&RTOLaserRangeFinderNode::spin, this));
}

RTOLaserRangeFinderNode::~RTOLaserRangeFinderNode()
{
}

void RTOLaserRangeFinderNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	laser_range_finder_.setComId( com_.id() );

	// Set the LaserRangeFinder numbers
	laser_range_finder_.setNumber( laserRangeFinderNumber_, this );

	com_.connectToServer( false );
}

void RTOLaserRangeFinderNode::spin()
{
	rclcpp::Time curr_time = rclcpp::Clock().now();
	laser_range_finder_.setTimeStamp(curr_time);

	com_.processEvents();
}

