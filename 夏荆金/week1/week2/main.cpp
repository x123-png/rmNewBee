#include "robot.h"
#include <iostream>
using namespace std;

int main(){
    int num_t=0;//id
    string command=" ",name,task;//命令，机器人名称，任务
    cout<<"请输入机器人名称；";
    cin>>name;
    Robot robot(name);//创建对象
    while(1){
        cout<<"请输入命令（添加/执行/显示/退出）：";
        cin>>command;
        if(command=="添加"){
            cin>>num_t>>task;
            robot.addTask(num_t,task);
        }
        else if(command=="执行"){
            robot.execute();
        }
        else if(command=="显示"){
            robot.displayTask();
        }
        else if(command=="退出"){
            return 0;
        }
        else cout<<"无效指令，请重新输入!"<<endl;
    }

    return 0;
}