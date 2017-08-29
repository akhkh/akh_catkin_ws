#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "teleop_keyboard");
	ros::NodeHandle n;

    ros::Publisher takeoff_pub=n.advertise<std_msgs::Empty>("/bebop/takeoff",1);
    ros::Publisher land_pub=n.advertise<std_msgs::Empty>("/bebop/land",1);
    ros::Publisher reset_pub=n.advertise<std_msgs::Empty>("/bebop/reset",1);
    ros::Publisher cmdvel_pub=n.advertise<geometry_msgs::Twist>("/bebop/cmd_Vel",1);

    ros::Rate loop_rate(10);
    std_msgs::Empty msg_Empty;
    geometry_msgs::Twist msg_cmdvel;
	
    char getkey;
    string str;
    double speed = 0.1;
	
	while(ros::ok())
    {
        cout<<"\n\n\n<<Control>>\nT : Takeoff\tL : Land\tS : Stop\nW : Forward\tX : Backward\tD : Right\tA : Left\n";
        cout<<"<<Change Speed>>\nO : Speed Up\tP : Speed Down\n";
        cout<<"<<Current Speed>>\nCurrent Speed : %d"<<speed<<"\n";
        getline(cin, str);
        getkey = str.at(0);
        cout<<"\n\n";

        switch(getkey)
        {
        //takeoff
        case 'T':
        case 't':
            takeoff_pub.publish(msg_Empty);
            break;

        //land
        case 'L':
        case 'l':
            land_pub.publish(msg_Empty);
            break;

        //stop
        case 'S':
        case 's':
            msg_cmdvel.linear.x = 0;
            msg_cmdvel.angular.z = 0;
            cmdvel_pub.publish(msg_cmdvel);
            break;

        //forward
        case 'W':
        case 'w':
            msg_cmdvel.linear.x = speed;
            cmdvel_pub.publish(msg_cmdvel);
            break;

        //backward
        case 'X':
        case 'x':
            msg_cmdvel.linear.x = speed;
            cmdvel_pub.publish(msg_cmdvel);
            break;

        //left
        case 'A':
        case 'a':
            msg_cmdvel.angular.z = speed;
            cmdvel_pub.publish(msg_cmdvel);
            break;

        //right
        case 'D':
        case 'd':
            msg_cmdvel.angular.z = speed;
            cmdvel_pub.publish(msg_cmdvel);
            break;

        //speed up
        case 'O':
        case 'o':
            speed = speed + 0.1;
            if(speed > 0.9)
                speed = 0.9;
            break;

        //speed down
        case 'P':
        case 'p':
            speed = speed - 0.1;
            if(speed < 0.1)
                speed = 0.1;
            break;

        default:
            cout<<"\n\nWarning!! : Wrong Command!\n\n";
            break;
        }
		
		ros::spinOnce();
		
        //loop_rate.sleep();
	}
	return 0;
}


