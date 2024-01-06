#include "MappingROS.h"

MappingROS::MappingROS()
{
	map_sub_ = nh_.subscribe("map", 1, &MappingROS::mapCallback, this);
	odom_sub_ = nh_.subscribe("odom", 1, &MappingROS::odomCallback, this);

	transListener_ = new tf::TransformListener(nh_);
	mapInfo_ = NULL;
}


MappingROS::~MappingROS()
{
	map_sub_.shutdown();
}

void MappingROS:: mapCallback(const nav_msgs::OccupancyGrid& occupancyGrid)
{
	if(mapInfo_)
	{
		delete mapInfo_;
	}
	mapInfo_ = new MapInfo(occupancyGrid, occupancyGrid.header.frame_id);
	set_map((char *)&(*occupancyGrid.data.begin()),
		(int)mapInfo_->width,
		(int)mapInfo_->height,
		(float)mapInfo_->resolution,(float)mapInfo_->offset[0],(float)mapInfo_->offset[1]);
	
}

void  MappingROS::odomCallback(const nav_msgs::Odometry& odom)
{
	float x,y;
	double deg;
	if(!mapInfo_)
	{
		return;
	}
	bool s = poseToMap( transListener_, *mapInfo_, odom, &x,&y,&deg );
	if(s)
	{
		set_poseOnMap(x,y,deg);
	}
	else
	{
		set_poseOnMap((float)0,(float)0,(double)0);
	}
}

void MappingROS::setTimeStamp(ros::Time stamp)
{
	stamp_ = stamp;
}
