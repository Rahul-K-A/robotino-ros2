#ifndef MAPPINGROS_H_
#define MAPPINGROS_H_

#include "rec/robotino/api2/Mapping.h"
#include "transform.h"
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>

class MappingROS : public rec::robotino::api2::Mapping
{
public:
	MappingROS();
	~MappingROS();

	void setTimeStamp(ros::Time stamp);
private:
	ros::NodeHandle nh_;

	ros::Subscriber map_sub_;

	ros::Subscriber odom_sub_;
	
	ros::Time stamp_;

	tf::TransformListener* transListener_;

	void mapCallback(const nav_msgs::OccupancyGrid& occupancyGrid);

	void odomCallback(const nav_msgs::Odometry& odom);
	
	MapInfo* mapInfo_;
};

#endif /* MAPPINGROS_H_ */
