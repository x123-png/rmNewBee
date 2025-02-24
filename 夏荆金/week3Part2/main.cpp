#include "taskscheduler.h"
#include <iostream>
#include "task.h"
#include "robot.h"
using namespace std;

int main(){
    int num_t=0,priority=0;//id,优先级
    string command=" ",name=" ",task;//命令，机器人名称，任务
    TaskScheduler robot_list;
    // cout<<"Please input the robot name:";
    // cin>>name;
    Robot robot(name);//创建对象
    while(1){
        cout<<"Please input the command(add_task/execute_task/display_task/quit/delete_task/addRobot/deleteRobot/getRobot/Robotlist):";
        cin>>command;
        if(command=="add_task"){
            cin>>name>>num_t>>task>>priority;   
            robot_list.getRobot(name)->addTask(num_t,task,priority);
        }
        else if(command=="execute_task"){
            cin>>name;
            robot_list.getRobot(name)->execute();
        }
        else if(command=="display_task"){
            cin>>name;
            robot_list.getRobot(name)->displayTask();
        }
        else if(command=="delete_task"){
            cin>>name;
            robot_list.getRobot(name)->undoTask();
        }
        else if(command=="addRobot"){
            cin>>name;
            robot_list.addRobot(name);
        }
        else if(command=="deleteRobot"){
            cin>>name;
            robot_list.deleteRobot(name);
        }
        else if(command=="getRobot"){
            cin>>name;
            robot_list.getRobot(name)->displayTask();
        }
        else if(command=="Robotlist"){
            robot_list.RobotList();
        }
        else if(command=="quit"){
            return 0;
        }
        else cout<<"Invalid command, please re-enter!"<<endl;
    }

    return 0;
}