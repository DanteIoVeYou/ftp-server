#pragma once
#include "socket.hpp"
class Server
{
public:
    Server(uint16_t port = 2222) : _port(port) {}
    ~Server()
    {
        close(_sock);
    }
    void Init()
    {
        _sock = Socket::Create();
        Socket::Bind(_sock, _port);
        LOG(INFO, "init server success...");
    }
    
private:
    uint16_t _port; // 绑定端口
    int _sock;      // 套接字
};