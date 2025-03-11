#pragma once

#include <vector>
#include "task.h"
#include <map>
class Taskmanager{
    private:
        std::thread out_thread;//作为监视变量out，当out不为0时输出并将其置零，不用创建新的一个线程来执行task任务因为task执行时就会开启一个线程
        std::atomic<int> out;  // 
        std::vector<std::atomic<int> *> a; //设置为int指针是为了当a数组长度变化时数组之前的地址不变化，以免造成指针指向变化而成为空指针的问题
        std::vector<TaskBase *> task_pointer;//作为基类指针指向需要使用的类别
        std::map<int,TaskBase *> task_list;// 作为监视a_i的列表，通过下标来访问
         //触发一次回调callback {key} {msg}，调用标识符为key的任务的回调函数，参数为msg
    public:
        Taskmanager(){};
        void setout();//监视out变量监视变量out，当out不为0时，输出并将其置零
        void add_task(int key,int kind);//添加任务，标识符和任务类型
        void run();//运行函数
        void pop_task();//删除任务,从末尾删除一个任务pop
        void callback(int key,int msg);//回调函数
};