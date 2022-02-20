#include <ros/ros.h>
#include <turtlesim/Kill.h>
#include <turtlesim/Spawn.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "spawnturtles");
	ros::NodeHandle node_handle;

//	ros::service::waitForService("turtlesim/Spawn");

	//delete original turtle
	ros::ServiceClient client_kill = node_handle.serviceClient<turtlesim::Kill>("kill");
	turtlesim::Kill kill_turtle;
	kill_turtle.request.name = "turtle1";
	if(client_kill.call(kill_turtle))
	{
		ROS_INFO("%s has been killed", kill_turtle.request.name.c_str());
	}
	else
		ROS_ERROR("ERROR");
	
	//new turtle
	ros::ServiceClient client_spawn = node_handle.serviceClient<turtlesim::Spawn>("spawn");
	turtlesim::Spawn new_turtle;
	new_turtle.request.name = "ben_turtle";
	new_turtle.request.x = 3;
	new_turtle.request.y = 3;
	new_turtle.request.theta = 0;
	if(client_spawn.call(new_turtle))
	{
		ROS_INFO("%s has been spawned", new_turtle.request.name.c_str());
	}
	else
		ROS_ERROR("ERROR");
	return 0;
}

