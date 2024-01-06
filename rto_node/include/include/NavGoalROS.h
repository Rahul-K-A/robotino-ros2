#ifndef NAVGOALROS_H_
#define NAVGOALROS_H_

#include "rec/robotino/api2/NavGoal.h"
#include "transform.h"
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>
class NavGoalROS: public rec::robotino::api2::NavGoal
{
public:
	NavGoalROS();
	~NavGoalROS();

private:
	ros::NodeHandle nh_;

	ros::Publisher navGoal_pub_;

	ros::Subscriber map_sub_;

	geometry_msgs::PoseStamped navGoal_msg_;

	void navGoalEvent(float x,float y,double r);

	void mapCallback(const nav_msgs::OccupancyGrid& occupancyGrid);

	MapInfo* mapInfo_;
};

#endif /* NAVGOALROS_H_ */
