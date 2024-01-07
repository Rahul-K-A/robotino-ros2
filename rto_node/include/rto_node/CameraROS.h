/*
 * CameraROS.h
 *
 *  Created on: 08.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef CAMERAROS_H_
#define CAMERAROS_H_

#include "rec/robotino/api2/Camera.h"

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "sensor_msgs/msg/camera_info.hpp"

class CameraROS : public rec::robotino::api2::Camera
{
public:
	CameraROS();
	~CameraROS();

	void setNumber( int number, rclcpp::Node * parent_node );
	void setTimeStamp(rclcpp::Time stamp);

private:
	rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr streaming_pub_;

	sensor_msgs::msg::Image img_msg_;

	rclcpp::Time stamp_;

	void imageReceivedEvent(
			const unsigned char* data,
			unsigned int dataSize,
			unsigned int width,
			unsigned int height,
			unsigned int step );

};

#endif /* CAMERAROS_H_ */
