#pragma once

#include "socket.hpp"
static const std::string client_cmd_prompt = "cli:> ";
class Client
{
public:
    Client(std::string ip, uint16_t port) : _ip(ip), _port(port) {}
    ~Client() {}
    void Init()
    {
        _fd = Socket::Create();
        Socket::Connect(_fd, _ip, _port);
    }
    void Loop()
    {
        // RecvServerInfo();
        // SendAccount();
        while (true)
        {
            std::cout << "client_cmd_prompt";
            fflush(stdout);
            char buffer_cmd[1024];
            ssize_t size = read(0, buffer_cmd, sizeof(buffer_cmd) - 1);
            if (size < 0)
            {
            }
            buffer_cmd[size] = 0;
            int s = send(_fd, buffer_cmd, strlen(buffer_cmd), 0);
            char buffer[1024];
            int ss = recv(_fd, buffer, sizeof(buffer) - 1, 0);
            if (ss < 0)
            {
            }
            buffer[ss] = 0;
            std::cout << buffer << std::endl;
        }
    }

private:
    std::string _ip;
    uint16_t _port;
    int _fd;
};