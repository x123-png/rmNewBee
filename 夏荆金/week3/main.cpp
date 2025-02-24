#include "taskscheduler.h"
#include <iostream>
#include "task.h"
#include "robot.h"
using namespace std;

int main(){
    int num_t=0;//id
    string command=" ",name=" ",task;//命令，机器人名称，任务
    TaskScheduler robot_list;   //添加机器人
    // cout<<"Please input the robot name:";
    // cin>>name;
    Robot robot(name);//创建对象
    while(1){
        cout<<"Please input the command(add_task/execute/quit/delete/addRobot/deleteRobot/getRobot/Robotlist):";
        cin>>command;
        if(command=="add_task"){
            cin>>name>>num_t>>task;
            robot_list.getRobot(name)->addTask(num_t,task);
        }
        else if(command=="execute"){
            cin>>name;
            robot_list.getRobot(name)->execute();
        }
        else if(command=="delete"){
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
        else if(command=="getRobot"){  //查询
            cin>>name;
            robot_list.getRobot(name)->displayTask();
        }
        else if(command=="Robotlist"){  //获取机器人列表
            robot_list.RobotList();
        }
        else if(command=="quit"){
            return 0;
        }
        else cout<<"Invalid command, please re-enter!"<<endl;
    }

    return 0;
}