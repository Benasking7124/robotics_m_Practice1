#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "ben_number_pub");
	ros::NodeHandle node_handle;
	std_msgs::Int32 n;

	ros::Publisher pub = node_handle.advertise<std_msgs::Int32>("number_ben", 1000);
	ros::Rate loop_rate(1);
	ROS_INFO("initialized publish number");

	node_handle.getParam("/pub_number", n.data);
	while (ros::ok())
	{
		pub.publish(n);
		loop_rate.sleep();
	}
	return 0;
}

