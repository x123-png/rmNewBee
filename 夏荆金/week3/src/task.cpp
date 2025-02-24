#include "task.h"
//此部分函数用于获取任务id和更新任务状态
Task::Task(int id,std::string task_desc):m_id(id),m_task_desc(task_desc),m_task_status("unexecuted"){
      //外部启用需要使用作用域解析运算符，将任务id初始化为0
}

void Task::executeTask() {
    m_task_status="executed";  //ִ执行任务函数用于更新任务状态
}

int Task::getID(int id){
    m_id=id;  //获取任务id
    return m_id;
}

std::string Task::getDesc(std::string command){//添加任务指令   *获取变量时以get打头*
    m_task_desc=command;
    return m_task_desc;    
}

std::string Task::displayStatus() const{  //显示状态
    return m_task_status;
}

std::string Task::displayTask(){   //显示任务
    return m_task_desc;
}

void Task::addStatus(std::string statu){
    m_task_status=statu;
}
