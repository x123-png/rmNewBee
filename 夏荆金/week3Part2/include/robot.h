#include "task.h"
#include <vector>
#ifndef ROBOT_H
#define ROBOT_H

class Robot{
private: 
    std::string m_robotName;  //机器人名称
    std::vector<Task> taskArry;       //任务列表,任务id,任务状态及优先级
public:
    Robot(std::string robotName); //初始化机器人名称及清空任务列表，Task已经在Task.h中初始过了
    ~Robot();//析构函数
    void addTask(int inputNum,std::string command,int priority); //添加任务函数 *add打头表示添加操作而不是单纯的修改*
    void displayTask();//显示任务函数
    void execute();//执行任务
    std::string getName(std::string name);//获得机器人名称
    void undoTask();//消除最后一个任务
};

#endif