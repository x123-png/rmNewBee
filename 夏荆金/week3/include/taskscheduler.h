#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H
#include <map>
#include "robot.h"

class TaskScheduler{
    private:
        std::map<std::string,Robot *> list;  //string为机器人名，robot为机器人对象
    public:
        void addRobot(const std::string &RobotName);  //添加机器人
        void deleteRobot(const std::string &RobotName);//根据名称删除机器人
        Robot* getRobot(const std::string &RobotName); //根据名称查询机器人
        std::vector<std::string> RobotList();//获取所有机器人名称
};

#endif