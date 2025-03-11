#include "taskmanager.h"

#include <iostream>
using namespace std;
void Taskmanager::setout(){
    while(1){
        std::atomic<int> *p_out=&out;
        int val=p_out->exchange(0);
        if (val!=0)
        {
            printf("out:%d\n\n",val);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));    
    }    
}

void Taskmanager::add_task(int key,int kind){
    auto p2=a.empty()? &out:a.back();  //p2监视倒数第二个数字  std::vector<std::atomic<int> *>是指向原子int数据的指针std::vector<std::atomic<int *>>是指向int的原子指针
    a.push_back(new std::atomic<int>(0)); //a是int指针，添加int数据时要手动分配内存
    auto p1=a.back();

    TaskBase *p=nullptr;
    if( kind == 1){
        p=new Task1(key,p1,p2);  //指向第一类任务，创建一个新的task1类
    }
    else if( kind == 2){
        p=new Task2(key,p1,p2);
    } 
    else if( kind == 3){
        p=new Task3(key,p1,p2);
    } 
    task_pointer.push_back(p);
    task_list[key]=p;
    p->start();
    printf("add_task finish!\n\n");
} //两处分配内存，对a指向的int分配一次，对基类指针分配一次

void Taskmanager::pop_task(){
    auto p=task_pointer.back();
    task_pointer.pop_back();
    task_list.erase(p->key);
    p->stop();
    delete p;
    delete a.back();//释放分配的内存  
    a.pop_back(); //删除任务后也要删除被监视的数据
    printf("pop_back finish!\n\n");
}

void Taskmanager::callback(int key,int msg){
    if(task_list.count(key)){/****查找是否存在这个任务列表***** */
        task_list[key]->callback(msg);
        printf("callback finish!\n\n");
    }
    else cerr<<"Invalued!"<<endl;
}

void Taskmanager::run(){
    out_thread=std::thread(&Taskmanager::setout,this);
    while (true)
    {
        std::string cmd;
        cin>>cmd;
        if(cmd=="add_task"){
            int key,kind;
            cin>>key>>kind;
            add_task(key,kind);
        }
        else if(cmd=="pop_task"){
            if(!task_list.empty()){    //先判断列表是否为空          
                pop_task();
            }
            else cerr<<"task_list is empty!"<<endl<<endl;
        }
        else if(cmd=="callback"){
            int key,msg;
            cin>>key>>msg;
            callback(key,msg);
        }
    } 
}