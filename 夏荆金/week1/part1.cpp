//#### 任务目标：
// 本任务要求编写一个简易的机器人控制系统。
// #### 前置知识：
// 基本的输入输出、条件判断和循环控制。
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int x=0,y=0,distance=0,direction=0;//x,y轴的位置初始为0，移动的距离为0
    char command; //行动指令

    while (true)
    {
        //执行命令
        cin >>command;
        if(command=='w' || command=='W'){ //前进
            cin >>distance;   //先却确定有无距离需求再考虑是否需要距离录入
            if(direction==0) y+=distance;
            else if(direction==90) x+=distance;
            else if(direction==180) y-=distance;
            else if(direction==270) x-=distance;
        }
        else if(command=='s' || command=='S'){
            cin >>distance;
            if(direction==0) y-=distance;
            else if(direction==90) x-=distance;
            else if(direction==180) y+=distance;
            else if(direction==270) x+=distance;
        }
        else if(command=='d' || command=='D'){
            direction+=90;
            if(direction>=360) direction-=360;
        }
        else if(command=='a' || command=='A'){
            direction-=90;
            if(direction<=0) direction+=360;
        }

        //输出结果
        if(direction==0){
            cout <<"位置（"<<x<<","<<y<<"),方向:上"<<endl; 
        }
        else if(direction==90){
            cout <<"位置（"<<x<<","<<y<<"),方向:右"<<endl;
        }
        else if(direction==180){
            cout <<"位置（"<<x<<","<<y<<"),方向:下"<<endl;
        }
        else if(direction==270){
            cout <<"位置（"<<x<<","<<y<<"),方向:左"<<endl<<endl;
        }
    }
    
    return 0;
}