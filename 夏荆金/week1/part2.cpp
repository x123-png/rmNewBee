#include <iostream>
#include <cmath>
using namespace std;



int main(){//x,y轴初始位置，移动的距离,x方向的移动，y方向的移动，最近的距离，最近敌人的索引初始设为0，敌人的坐标x1，y1
    int x=0,y=0,distance=0,direction=0,x_move=0,y_move=0,min_distance,min_index=0,x_enemy[100],y_enemy[100],distance_enemy[100];
    char command,tmp; //行动指令

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
        
        int index=0; //敌人个数索引            
        cin >> tmp >> x_enemy[index]>>y_enemy[index];
        {//敌人信息的录入
            distance_enemy[index]=sqrt(pow(x_enemy[index]-x,2)+pow(y_enemy[index]-y,2));  //计算距离
            index++;  //自动移到下一位
            for(int i=0;i<index-1;i++){   //比较最小的敌人距离
                if(distance_enemy[i]<=distance_enemy[i+1]) min_index=i;
                else min_index=i+1;
            }
            
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
            cout <<"位置（"<<x<<","<<y<<"),方向:左"<<endl;
        }
        cout << "最近敌人位置: (" <<x_enemy[min_index]<<","<<y_enemy[min_index]<<"), 所需控制操作：[";
         //移动方向
        x_move=x_enemy[min_index]-x;
        y_move=y_enemy[min_index]-y;
        if(x_move>0 && y_move>0){  //第一象限
            if(direction==0){
                cout<<"w "<<y_move<<", d]"<<endl;
            }
            else if(direction==90){
                cout<<"w "<<x_move<<", a]"<<endl;
            }
            else if(direction==180){
                cout<<"s "<<y_move<<", a]"<<endl;
            }
            else if(direction==270){
                cout<<"s "<<x_move<<", d]"<<endl;
            }
        }
        else if(x_move<0 && y_move>0){  //第二象限
            x_move=-x_move;
            if(direction==0){
                cout<<"w "<<y_move<<", a"<<endl;
            }
            else if(direction==90){
                cout<<"s "<<x_move<<", a]"<<endl;
            }
            else if(direction==180){
                cout<<"s "<<y_move<<", d]"<<endl;
            }
            else if(direction==270){
                cout<<"w "<<x_move<<", d"<<endl;
            }
        }
        else if(x_move<0 && y_move<0){  //第三象限
            x_move=-x_move;
            y_move=-y_move;
            if(direction==0){
                cout<<"s "<<y_move<<", a]"<<endl;
            }
            else if(direction==90){
                cout<<"s "<<x_move<<", d]"<<endl;
            }
            else if(direction==180){
                cout<<"w "<<y_move<<", d]"<<endl;
            }
            else if(direction==270){
                cout<<"w "<<x_move<<", a]"<<endl;
            }
        }
        else if(x_move>0 && y_move<0){  //第四象限
            y_move=-y_move;
            if(direction==0){
                cout<<"s "<<y_move<<", d]"<<endl;
            }
            else if(direction==90){
                cout<<"w "<<x_move<<", d]"<<endl;
            }
            else if(direction==180){
                cout<<"w "<<y_move<<", a]"<<endl;
            }
            else if(direction==270){
                cout<<"s "<<x_move<<", a]"<<endl;            
            }        
        }
        else if(x_move==0 && y_move>0){ //y轴正半轴
            if(direction==0) cout<<"]"<<endl;
            else if(direction==90) cout<<"a]"<<endl;
            else if(direction==180) cout<<"d, d]"<<endl;
            else if(direction==270) cout<<"d]"<<endl;        
        }
        else if(x_move==0 && y_move<0){ //y轴负半轴
            if(direction==0) cout<<"d, d]"<<endl;
            else if(direction==90) cout<<"d]"<<endl;
            else if(direction==180) cout<<"]"<<endl;
            else if(direction==270) cout<<"a]"<<endl;
        }
        else if(x_move>0 && y_move==0){ //x正半轴
            if(direction==0) cout<<"d]"<<endl;
            else if(direction==90) cout<<"]"<<endl;
            else if(direction==180) cout<<"a]"<<endl;
            else if(direction==270) cout<<"d ,d]"<<endl;
        }
        else if(x_move<0 && y_move==0){  //x负半轴
            if(direction==0) cout<<"d, d]"<<endl;
            else if(direction==90) cout<<"d]"<<endl;
            else if(direction==180) cout<<"a]"<<endl;
            else if(direction==270) cout<<"]"<<endl;
        }
    }
   
    return 0;
}
