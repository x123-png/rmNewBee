#include "task.h"
#ifndef ROBOT_H
#define ROBOT_H

class Robot{
private: 
    std::string m_robotName;  //机器人名称
    Task taskArry[100];       //任务列表,任务id及任务状态
    int task_index;    //任务列表索引
public:
    Robot(std::string robotName); //初始化机器人名称及清空任务列表，Task已经在Task.h中初始过了
    ~Robot();//析构函数
    void addTask(int inputNum,std::string command); //添加任务函数
    void displayTask();//显示任务函数
    void execute();//执行任务
    std::string getName(std::string name);//获得机器人名称
    //void returnDisplay();//退出时展示
};

#endif