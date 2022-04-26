#include "ros/ros.h"
#include "numprint/numprint.h"
#include <iostream>

int i = 0;

bool count(numprint::numprint::Request  &req, numprint::numprint::Response &res)
{
	int flag;
	flag = req.num;
	
	//数字在0～100范围内，更新i
	if(flag>=0 && flag<=100){
	ROS_INFO("receive a number %d from keyboard", flag);
	i = flag;	
	}
	
	//res.tips ="Now, counting from the number you have entered.";
	return true;
}


int main(int argc, char **argv)
{
	
	//初始化节点
	ros::init(argc, argv, "numprint_server");

	//句柄，实例化node	
	ros::NodeHandle n;
	
	//创建一个server，注册回调函数count
	ros::ServiceServer service = n.advertiseService("numprint", count);	
	ROS_INFO("couter start and wait for entering number.");
	
	//设置2s的间隔
	ros::Rate loop_rate(0.5);

	while(ros::ok())
	{

	//查看回调函数，根据输入数字更新i
		ros::spinOnce();

	//睡眠等到间隔时间达到
		loop_rate.sleep();

		std::cout << i << std::endl;
		i++;
		if(i>100)
		{
			i = 0;
		}
	}
	return 0;
}

