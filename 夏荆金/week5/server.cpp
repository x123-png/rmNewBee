#include <iostream>
#include <cstring>
#include <string>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <sstream>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#pragma comment(lib,"ws2_32.lib")  //连接windows套接字库

using namespace std;

mutex log_mutex;
mutex food_mutex;

struct ingredients
{
    char id;
    string name;
    string part;
};

struct stock
{
    vector<string> stockName;
    vector<int> left;
};

struct log_part{
    vector<int> curr;
    vector<string> name;
};

int main(){
    //初始化winsock版本,在任何winsock函数调用前执行
    WSADATA wsaData; //包含winsock系统细节的结构体
    WSAStartup(MAKEWORD(2,2),&wsaData);//初始化Winsock，请求winsock2.2版本。并与WSAClearup（）配对使用

    //创建监听套接字
    //IPv4地址族，面向连接的套接字（效率低但可以重复发送且检查信息是否正确），确定使用默认协议
    SOCKET listen_socket = socket(AF_INET,SOCK_STREAM,0);
    //检查是否连创建或初始化失败
    if(listen_socket==INVALID_SOCKET){  //检查是否连接成功
        cerr<<"socket创建失败 error"<<endl;
        return -1;
    }

    //地址绑定与监听（bind（）），IPv4的socket结构体，储存ip地址和端口号
    struct sockaddr_in local={0}; //并初始化
    local.sin_family = AF_INET; //指定地址族，AF_INET表示IPv4（AF_INET6是ipv6） 
    local.sin_addr.s_addr=INADDR_ANY; //储存ip地址，绑定所有可用接口
    local.sin_port=htons(9999);//设置主机端口号，与客户端连接
    //绑定失败
    if(bind(listen_socket,(struct sockaddr*)&local,sizeof(local))==INVALID_SOCKET){//bind(要绑定的套接字，指向包含地址和端口信息的socket结构的指针,sockaddr的结构体长度)
        cerr<<"bind error"<<endl;
        return -1;
    }
    //监听失败
    if(listen(listen_socket,128)==SOCKET_ERROR){ //listen(SOCKET 要设置为监听状态的套接字,int 等待列队的最大长度)
        cerr<<"listen error"<<endl;
        return -1;
    }

    //
    while(1){  //            正在监听的套接字，指向sockaddr结构的指针用于接收客户端地址信息可以为空，指向addr结构长度的指针，可以为空。  
        SOCKET client_socket=accept(listen_socket,nullptr,nullptr);
        if(client_socket == INVALID_SOCKET){ //如果连接失败，则跳过重新连接
            continue;
        }
        cout<<"client connect:"<<client_socket<<endl;//成功连接返回一个新的socket（clien_socket)否则返回INVALID_SOCKET
       //为每个新连接创建一个专属线程
       //lambda表达式[](...){...} 捕获的列表，列表的参数
        thread th([](SOCKET client_socket){
            int answer;   
            fstream food;
            ofstream log;
            food.open("D:\\github\\夏荆金\\week5\\food.txt",ios::out|ios::in);  // 
            if(food.is_open()==false){
                cerr<<"打开food文件失败:";
                return -1;
            }
            ifstream menu;
            menu.open("D:\\github\\夏荆金\\week5\\menu.txt",ios::in);  //
            if(menu.is_open()==false){
                cerr<<"打开menu文件失败:";
                return -1;
            }
            log.open("D:\\github\\夏荆金\\week5\\log.txt",ios::app);
            if(log.is_open()==false){
                cerr<<"打开log文件失败:";
                return -1;
            }
            while(1){
                char buffer[1024]={0};
                //int buffer;
                //ret表示实际读取的字节数
                int ret=recv(client_socket,buffer,sizeof buffer,0);//接收数据的套接字，用于储存接收数据的缓冲区，缓冲区的大小，标志位
                if(ret<=0){
                    cout<<"client disconnect:"<<client_socket<<endl;
                    break;
                }               
                lock_guard<mutex> lock1(log_mutex);
                lock_guard<mutex> lock2(food_mutex);
                //对文件内容进行更改
                
                menu.clear();
                menu.seekg(0);
                const char* message;
                int n=buffer[0]-'0';
                string ingr_tmp;    
                ingredients ingr;   
                for(int i=0;i<n-1;i++){  //文件位置在需要部分的上一行末尾
                    getline(menu,ingr_tmp); 
                }
                menu>>ingr.id>>ingr.name;//获得菜单的配料信息
                //cout<<"ingr.name:"<<ingr.name<<endl;
                getline(menu,ingr.part);   //获取剩下配料信息      
                //遍历每个食材
                log_part log_part;
                string tmp;
                istringstream iss(ingr.part);
                stock leftFood; //
                bool finish=true;
                while (iss>>tmp)
                {
                    int index=0;
                    log_part.name.push_back(tmp);  //放入log中的食材
                    leftFood.stockName={""};
                    //cout<<"tmp:"<<tmp<<endl;
                    food.clear();
                    food.seekg(0);
                    while (leftFood.stockName[index]!=tmp)
                    {
                        string nameTmp;
                        int foodTmp;
                        if(!(food>>nameTmp>>foodTmp)) break;
                        leftFood.stockName.push_back(nameTmp);
                        leftFood.left.push_back(foodTmp);
                        //if(!(food>>leftFood.stockName[index]>>leftFood.left[index])) break;//下行不用再读取这一行已经读取过了
                        //else food>>leftFood.stockName>>leftFood.left;  //stock的作用是检查储存文件中食物的剩余量
                        //cout<<"leftFood.stockName"<<leftFood.stockName<<" leftFood.left:"<<leftFood.left<<endl;
                        index++;
                    }
                    //将文件移动到数字位置

                    // auto pos=food.tellg();
                    // long position=(long)pos-9; 
                    // string check;  ///////////////////////////////////////
                    // food.seekp(position,ios::beg);  
                    // while (food>>check)
                    // {
                    //     cout<<check<<endl;
                    // }
                    //leftFood.left-=1;
                    

                    // food<<leftFood.left; 
                }                        

                int do1=1;
                for(int i=0;i<leftFood.left.size();i++){
                    if(leftFood.left[i]==0) do1=0;
                }
                if(do1)
                {
                    for(int i=0;i<leftFood.left.size();i++){
                        leftFood.left[i]-=1;
                    }
                }
                else finish=false;

                for(int i=0;i<leftFood.left.size();i++){
                    log_part.curr.push_back(leftFood.left[i]);  //写入日志的食物当前剩余量
                }
                
                
                //写入log日志的内容
                auto now = std::chrono::system_clock::now(); //写入时间
                std::time_t now_time = std::chrono::system_clock::to_time_t(now);
                std::tm* now_tm = std::localtime(&now_time); 
                log<<std::put_time(now_tm, "%H-%M-%S")<<" "<<ingr.name<<" ";
                if(finish){
                    message="1";
                    log<<"完成订单 ";
                }
                else{
                    log<<"未完成订单 ";
                    message="0";
                }
                log<<"[";
                for(int i=0;i<log_part.name.size();i++){
                    log<<log_part.name[i]<<" "<<log_part.curr[i]<<";";
                    }
                    log<<"]"<<endl;                          
                
                answer=send(client_socket,message,strlen(message),0);
                //send(client_socket,buffer,strlen(buffer),0);//使用send把同样的内容发回客户端
            }           
            food.close();
            menu.close();
            log.close(); 
            //return answer;
            closesocket(client_socket); //连接结束时关闭这个专用连接 
        },client_socket);
        th.detach(); //该线程结束后自动回收资源，是单独的资源
    }
    return 0;
}    