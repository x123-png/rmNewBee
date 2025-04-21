#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main(){
    //初始化Winsock库
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    //创建客户端socket
    SOCKET client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket==INVALID_SOCKET){
        cerr<<"socket创建失败"<<endl;
        return -1;
    }

    //设置目标服务器地址
    struct sockaddr_in target;
    target.sin_family = AF_INET; //使用IPv4协议
    target.sin_port=htons(9999); //端口号，htons将主机字节序转换为网络字节序
    target.sin_addr.s_addr = inet_addr("127.0.0.1");
    //inet_pton(AF_INET,"127.0.0.1",&target.sin_addr.s_addr);//将ip地址改为二进制形式

    //连接到服务器
    if(connect(client_socket,(struct sockaddr*)&target,sizeof target)==INVALID_SOCKET){
        cerr<<"connect error"<<endl;
        closesocket(client_socket);
        return -1;
    }

    while(1){
        int dish;
        //cin>>dish;
        //char dish[1024]={0};
        cout<<"dish:";
        cin>>dish;
        char n='0'+dish;
        send(client_socket,&n,sizeof(dish),0);

        char buffer[1024]={0};
        int ret=recv(client_socket,buffer,sizeof(buffer),0);
        if(ret<=0){
            cout<<"server disconnect."<<endl;
        }

        cout<<buffer<<endl;
    }
    closesocket(client_socket);
    return 0;
}