#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

char getch()
{
	int flags = fcntl(0, F_GETFL, 0);
	fcntl(0, F_SETFL, flags | O_NONBLOCK);

	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0) 
	{
		perror("tcsetattr()");
	 }
	 old.c_lflag &= ~ICANON;
	 old.c_lflag &= ~ECHO;
	 old.c_cc[VMIN] = 1;
	 old.c_cc[VTIME] = 0;
	 if (tcsetattr(0, TCSANOW, &old) < 0) 
	 {
		 perror("tcsetattr ICANON");
	 }
	 if (read(0, &buf, 1) < 0) 
	 {
		 perror ("read()");
	 }
	 old.c_lflag |= ICANON;
	 old.c_lflag |= ECHO;
	 if (tcsetattr(0, TCSADRAIN, &old) < 0) 
	 {
		 perror ("tcsetattr ~ICANON");
	 }
	 
	 return (buf);
}

int main(int argc, char **argv)
{
	char input = 0;
	geometry_msgs::Twist cmd;
	ros::init(argc, argv, "ben_turtle_control");
	ros::NodeHandle node_handle;
	
	ros::Publisher pub = node_handle.advertise<geometry_msgs::Twist>("ben_turtle/cmd_vel", 1000);
	while (ros::ok())
	{
		input = getch();
		switch (input)
		{
			case 'w':
				cmd.linear.x = 1;
				break;
			case 's':
				cmd.linear.x = -1;
				break;
			case 'a':
				cmd.angular.z = 1;
				break;
			case 'd':
				cmd.angular.z = -1;
				break;
			case 'r':
				cmd.linear.x = 0;
				cmd.angular.z = 0;
				break;
		}
		pub.publish(cmd);
	}
	return 0;
}
