/*
 * RTONode.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef RTOCameraNode_H
#define RTOCameraNode_H

#include "ComROS.h"
#include "CameraROS.h"

#include "rclcpp/rclcpp.hpp"

class RTOCameraNode : public rclcpp::Node
{
public:
	RTOCameraNode();
	~RTOCameraNode();


private:
	void spin();
	rclcpp::TimerBase::SharedPtr timer_;
	std::string hostname_;
	int cameraNumber_;

	ComROS com_;
	CameraROS camera_;

	void initModules();

};

#endif /* RTOCameraNode_H */
