#include "RTOMappingNode.h"

RTOMappingNode::RTOMappingNode()
	: nh_("~")
{
	nh_.param<std::string>("hostname", hostname_, "192.168.5.5" );

    com_.setName( "Mapping" );

    initModules();
}

RTOMappingNode::~RTOMappingNode()
{
}

void RTOMappingNode::initModules()
{
	com_.setAddress( hostname_.c_str() );

	// Set the ComIds
	mappingRos_.setComId( com_.id() );
	initialPoseROS_.setComId( com_.id() );
	navGoalROS_.setComId( com_.id() );
	
	com_.connectToServer( false );
}

bool RTOMappingNode::spin()
{
	ros::Rate loop_rate( 30 );

	while(nh_.ok())
	{
        ros::Time curr_time = ros::Time::now();
        mappingRos_.setTimeStamp(curr_time);

        com_.processEvents();
        ros::spinOnce();
		loop_rate.sleep();
	}
	return true;
}

