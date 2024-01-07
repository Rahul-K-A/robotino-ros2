/*
 * ComROS.h
 *
 *  Created on: 06.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef COMROS_H_
#define COMROS_H_

#include "rec/robotino/api2/Com.h"

#include "rclcpp/rclcpp.hpp"
#include <string>

class ComROS: public rec::robotino::api2::Com
{
public:
	ComROS(rclcpp::Node* parent_node_ptr);
	~ComROS();

	void setName( const std::string& name );

private:
	rclcpp::Node* parent_node;
	std::string name_;
	void errorEvent( const char* errorString );
	void connectedEvent();
	void connectionClosedEvent();
};

#endif /* COMROS_H_ */
