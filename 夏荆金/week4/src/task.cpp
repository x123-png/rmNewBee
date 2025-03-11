#include "task.h"
#include <iostream>

void sleep_func(int t){
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
}

void TaskBase::start(){
    handler=std::thread(&TaskBase::run,this);
}

void TaskBase::stop(){
    finish=true;
    handler.join();
}

void Task1::run(){
    while (!finish)  //判断条件是否程序停止,若程序未停止
    {
        int val=p1->exchange(0);  //防止多线程导致p1的值已经变化，将p1值先与0交换
        if (val!=0) //val的值是不会变化的，只需判断一次
        {
            *p2=val+1;
            printf("write 1_%d:%d\n\n",key,val+1);
        }  
        sleep_func(1);   
    }// 使用cout输出流时同时存在多个输出会出现混乱
}    
    

void Task1::callback(int msg){
    *p1=msg;      
}

void Task2::run(){
    while (!finish)
    {    
        int val=p1->exchange(0);
        if (val!=0)
        {
            *p2=val*k;
            printf("write 2_%d:%d\n\n",key,val*k);
        }        
        sleep_func(1);
    }    
}
    
void Task2::callback(int msg){
    k=msg;
    *p1=1;     
}

void Task3::run(){
    while (!finish)
    {
        int t=p1->exchange(0);    
        if (t!=0)
        {
            *p2=t;    
            printf("write 3_%d:%d\n\n",key,t);
            sleep_func(1); 
            *p2=t+1;  
            printf("write 3_%d:%d\n\n",key,t+1);
        }
        sleep_func(1); 
    }
}

void Task3::callback(int msg){
    *p1=msg;  
}
