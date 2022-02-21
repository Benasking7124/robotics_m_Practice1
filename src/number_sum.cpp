#include <ros/ros.h>
#include <std_msgs/Int32.h>

class Number_Summation
{
private:
	int num, num_ben, num_freddy;
	ros::Publisher pub;
	ros::Subscriber number_ben_sub;
	ros::Subscriber number_freddy_sub;

public:
	Number_Summation(ros::NodeHandle &nh)
	{
		num = 0;
		pub = nh.advertise<std_msgs::Int32>("number_sum_ben", 1000);
		number_ben_sub = nh.subscribe("number_ben", 1000, &Number_Summation::callback_number_ben, this);
		number_freddy_sub = nh.subscribe("number_freddy", 1000, &Number_Summation::callback_number_freddy, this);
	}

	void callback_number_ben(const std_msgs::Int32 &msg)
	{
		num_ben = msg.data;
		num = num_ben + num_freddy;
		ROS_INFO("%d", num);
	}
	void callback_number_freddy(const std_msgs::Int32 &msg)
	{
		num_freddy = msg.data;
		num = num_ben + num_freddy;
		ROS_INFO("%d", num);
	}
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "ben_number_sum");
	ros::NodeHandle node_handle;
	Number_Summation n_sum(node_handle);

	ros::spin();

	return 0;
}
