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
#include <image_transport/image_transport.h>

class CameraROS : public rec::robotino::api2::Camera, rclcpp::Node
{
public:
	CameraROS();
	~CameraROS();

	void setNumber( int number );
	void setTimeStamp(rclcpp::Time stamp);

private:
	image_transport::ImageTransport img_transport_;
	image_transport::CameraPublisher streaming_pub_;

	sensor_msgs::msg::Image img_msg_;
	sensor_msgs::msg::CameraInfo cam_info_msg_;

	rclcpp::Time stamp_;

	void imageReceivedEvent(
			const unsigned char* data,
			unsigned int dataSize,
			unsigned int width,
			unsigned int height,
			unsigned int step );

};

#endif /* CAMERAROS_H_ */
