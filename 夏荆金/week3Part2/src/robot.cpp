#include "robot.h"
#include <iostream>
#include <vector>
using namespace std;

Robot::Robot(string robotName):m_robotName(" "){};//初始化名称

Robot::~Robot(){  //创建对象生命周期结束时会调用析构函数
    for(int i=0;i<taskArry.size();i++){
        if(taskArry[i].displayStatus()=="unexecuted"){
            cout<<"unexecuted Task id:";
            cout<<i+1<<" ,task_describ:"<<taskArry[i].displayTask()<<endl;
        }
    }
}


void Robot::addTask(int id,string desc,int prioioty){  //添加
    taskArry.push_back(Task(id,desc,prioioty)); //任务添加
    sort(taskArry.begin(),taskArry.end(),Task::cmp);//降序排序
}

void Robot::displayTask(){    //显示
    for(int i=0;i<taskArry.size();i++){
        cout<<"Task id:"<<i+1<<" ,describ:"<<taskArry[i].displayTask()<<" status:"<<taskArry[i].displayStatus()<<endl;
    }
}

void Robot::execute(){    //执行，此时从最高项开始执行
    taskArry[0].executeTask();
}

string Robot::getName(string name){  //获取机器人名称  ，在构造函数时输入了姓名不需要再加其他函数专门输入机器人姓名
    m_robotName=name;
    return m_robotName;
}

void Robot::undoTask(){
    taskArry.pop_back();  //删除最后一个任务,此时排序好后删除的就是最小的任务
}