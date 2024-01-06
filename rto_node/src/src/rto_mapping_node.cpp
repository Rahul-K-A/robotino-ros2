#include "RTOMappingNode.h"

#include <ros/ros.h>


int main(int argc, char** argv)
{
	ros::init(argc, argv, "rto_mapping_node");
    RTOMappingNode rn;
    rn.spin();
    ros::spin();
	return 0;
}
