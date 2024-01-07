/*
 * EncoderInputROS.h
 *
 *  Created on: 09.12.2011
 *      Author: indorewala@servicerobotics.eu
 */

#ifndef ENCODERINPUTROS_H_
#define ENCODERINPUTROS_H_

#include "rec/robotino/api2/EncoderInput.h"

#include "rclcpp/rclcpp.hpp"
#include "rto_msgs/msg/encoder_readings.hpp"
#include "rto_msgs/srv/set_encoder_position.hpp"


class EncoderInputROS: public rec::robotino::api2::EncoderInput
{
public:
	EncoderInputROS(rclcpp::Node* parent_node);
	~EncoderInputROS();

	void setTimeStamp(rclcpp::Time stamp);

private:
	rclcpp::Publisher<rto_msgs::msg::EncoderReadings>::SharedPtr encoder_pub_;

	rclcpp::Service<rto_msgs::srv::SetEncoderPosition>::SharedPtr encoder_position_server_;

	rto_msgs::msg::EncoderReadings encoder_msg_;

	rclcpp::Time stamp_;

	void readingsChangedEvent( int velocity, int position, float current );

	bool setEncoderPositionCallback(
			const std::shared_ptr<rto_msgs::srv::SetEncoderPosition::Request> req,
			const std::shared_ptr<rto_msgs::srv::SetEncoderPosition::Response> res);
};

#endif /* ENCODERINPUTROS_H_ */
