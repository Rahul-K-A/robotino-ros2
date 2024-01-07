/*
 * BumperROS.h
 *
 *  Created on: 06.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef BUMPERROS_H_
#define BUMPERROS_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

#include "rec/robotino/api2/Bumper.h"


class BumperROS: public rec::robotino::api2::Bumper
{
public:
	BumperROS();
	~BumperROS();

private:
	std_msgs::msg::Bool bumper_msg_;
	rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr bumper_pub_;




	void bumperEvent(bool hasContact);
};

#endif /* BUMPERROS_H_ */
