#include "robot.h"
#include <iostream>
using namespace std;

Robot::Robot(string robotName):m_robotName(" "),task_index(0){};//初始化名称

Robot::~Robot(){  //创建对象生命周期结束时会调用析构函数
    for(int i=0;i<task_index;i++){
        if(taskArry[i].displayStatus()=="待执行"){
            cout<<"待执行任务 id:";
            cout<<i+1<<" ,描述："<<taskArry[i].displayTask()<<endl;
        }
    }
}

void Robot::addTask(int inputNum,string command){  //添加
    taskArry[task_index].getID(inputNum);
    taskArry[task_index].getDesc(command);
    taskArry[task_index].addStatus("待执行");
    task_index++;
}

void Robot::displayTask(){    //显示
    for(int i=0;i<task_index;i++){
        cout<<"任务id:"<<i+1<<"，描述："<<taskArry[i].displayTask()<<" 状态："<<taskArry[i].displayStatus()<<endl;
    }
}

void Robot::execute(){    //执行
    for(int i=0;i<task_index;i++){
        taskArry[i].executeTask();
    }
    
}

string Robot::getName(string name){  //获取机器人名称
    m_robotName=name;
    return m_robotName;
}

// void Robot::returnDisplay(){

// }