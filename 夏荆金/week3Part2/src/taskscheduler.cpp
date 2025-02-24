#include "taskscheduler.h"
#include <iostream>

void TaskScheduler::addRobot(const std::string &RobotName){
    if(list.count(RobotName)){  //如果本身的robot里面存在这个机器人,则显示错误
        std::cerr<<"has:"<<RobotName<<std::endl;
        return;
    }
    list[RobotName]=new Robot(RobotName);//若不存在则添加该机器人到Robot类中。[键] = 值 
}

void TaskScheduler::deleteRobot(const std::string &RobotName){
    if(!list.count(RobotName)){ //如果不存在该robot直接返回
        return;
    }
    list.erase(RobotName);//存在则删除该机器人
    delete list[RobotName];//释放内存
}

Robot* TaskScheduler::getRobot(const std::string &RobotName){
    if(!list.count(RobotName)){ //如果不存在该robot返回空指针        
        return nullptr;
    }
    return list[RobotName];  //存在返回robot对象
}

std::vector<std::string> TaskScheduler::RobotList(){
    std::vector<std::string> sublist;  //作为返回的vector值
    std::cout<<"RobotName list:"<<std::endl;
    for(auto it:list){
        sublist.push_back(it.first);  //返回机器人名称，first是键的值，即返回机器人名称
        std::cout<<it.first<<std::endl;
    }

}