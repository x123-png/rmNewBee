#pragma once

#include <atomic>
#include <thread>
class TaskBase{   //基类task
    public:
        TaskBase(int key,std::atomic<int> *p1,std::atomic<int> *p2):key(key),p1(p1),p2(p2){};
        //TaskBase(int key,std::atomic<int> *p1,std::atomic<int> *p2):key(key),p1(p1),p2(p2),finish(true){};
        int key;  //关键标识符，监视数据指针1，储存数据指针2
        std::atomic<bool> finish; //函数是否进行的条件
        virtual void callback(int msg)=0; //回调函数
        virtual void run()=0;  //运行函数
        void start();//开始函数
        void stop(); //停止函数
        virtual ~TaskBase(){};
    protected:
        std::atomic<int> *p1=nullptr,*p2=nullptr;
    private:
        std::thread handler;        
};

class Task1:public TaskBase{
    public:
        Task1(int key,std::atomic<int> *p1,std::atomic<int> *p2):TaskBase(key,p1,p2){};
        void run() override;   //将(*p1) + 1的值写入*p2，将*p1置零
        void callback(int msg) override; //callback(int msg)：将*p1的值修改为msg
};

class Task2:public TaskBase{
    public:
        Task2(int key,std::atomic<int> *p1,std::atomic<int> *p2):TaskBase(key,p1,p2){};
        int k=1;    //系数比例
        void run() override; //运算：将(*p1) * k的值写入*p2，将*p1置零
        void callback(int msg) override; //将k的值修改为msg，并将*p1修改为1
};

class Task3:public TaskBase{
    public:
        Task3(int key,std::atomic<int> *p1,std::atomic<int> *p2):TaskBase(key,p1,p2){};
        void run() override;  //将*p1的值暂存为t，将*p1置零，将t写入*p2，延迟1ms后将t + 1写入*p2
        void callback(int msg) override;//将*p1的值修改为msg
};      
