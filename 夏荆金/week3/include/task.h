#ifndef TASK_H
#define TASK_H
#include <string>

class Task{
private: 
    int m_id;            //任务id
    std::string m_task_desc;  //任务描述
    std::string m_task_status;  //任务状态
public:     //成员函数声明
    Task(){};//默认构造函数
    Task(int id,std::string task_desc);  //构造函数，参数为编号、执行状态
    void executeTask() ;  //执行任务函数,更新任务状态
    std::string displayStatus() const;//显示任务状态
    int getID(int id);    //获得任务id
    std::string getDesc(std::string command);//获得任务描述
    std::string displayTask();//显示状态
    void addStatus(std::string statu);//添加状态
};



#endif