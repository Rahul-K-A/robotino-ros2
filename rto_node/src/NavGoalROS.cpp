#include "NavGoalROS.h"

NavGoalROS::NavGoalROS()
{
	navGoal_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1, true);

	mapInfo_ = NULL;
	map_sub_ = nh_.subscribe("map", 1, &NavGoalROS::mapCallback, this);

}

NavGoalROS::~NavGoalROS()
{
	navGoal_pub_.shutdown();
	map_sub_.shutdown();
}

void NavGoalROS:: navGoalEvent(float x,float y,double r)
{
	if(mapInfo_)
	{
		navGoal_msg_.pose.position.x = ( -mapInfo_->resolution * (x + mapInfo_->offset[0] ) );
		navGoal_msg_.pose.position.y = ( mapInfo_->resolution * ( y + mapInfo_->offset[1] ) );

		navGoal_msg_.pose.position.z = 0;
	
		double rot = deg2rad( r );
		double rx = cos( rot );
		double ry = sin( rot );
		rot = atan2( ry, -rx );

		tf::Quaternion q = tf::createQuaternionFromYaw( rot );
		navGoal_msg_.pose.orientation.x = q.x();
		navGoal_msg_.pose.orientation.y = q.y();	
		navGoal_msg_.pose.orientation.z = q.z();
		navGoal_msg_.pose.orientation.w = q.w();

		navGoal_msg_.header.frame_id = mapInfo_->frame_id;
		navGoal_msg_.header.stamp = ros::Time::now();

		navGoal_pub_.publish(navGoal_msg_);

	}
}

void NavGoalROS::mapCallback(const nav_msgs::OccupancyGrid& occupancyGrid)
{
	if(mapInfo_)
	{
		delete mapInfo_;
	}
	mapInfo_ = new MapInfo(occupancyGrid, occupancyGrid.header.frame_id);
}
