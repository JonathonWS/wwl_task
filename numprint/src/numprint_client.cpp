#include "ros/ros.h"
#include "numprint/numprint.h"
#include <iostream>

using namespace std;
int main(int argc, char** argv)
{

	//初始化节点，创建句柄，创建client
	ros::init(argc, argv, "numprint_client");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<numprint::numprint>("numprint");
	numprint::numprint srv;
	int i;

	//借助ros::ok()，实现循环输入数字
	while(ros::ok()){
		do{
			ROS_INFO("please enter a number between 0 and 100: ");
			cin >> i;

	//输入的数字不在范围内，提示重新输入
			while(i>100 || i<0){
				ROS_INFO("number should between 0 and 100, please enter again:");
				break;
			}
			srv.request.num = i;
			if(client.call(srv) && (i>=0 && i<=100)){
			ROS_INFO("send a number %d successfully.", i);
			}
			else{
				ROS_INFO("failed to call server.");
			}
		}while(0);
		
	}
	return 0;
}
