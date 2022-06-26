#pragma once
#include "common.hpp"
#include "log.hpp"
class Socket
{
public:
    Socket() {}
    ~Socket() {}
    static int Create()
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
        {
            LOG(FATAL, "socket create error");
            exit(SOCK_CREATE);
        }
        else
        {
            return sock;
        }
    }
    static void Bind(int fd, uint16_t port)
    {
        sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;
        if (bind(fd, (sockaddr *)&local, sizeof(local)) < 0)
        {
            LOG(FATAL, "socket bind error");
            exit(SOCK_BIND);
        }
    }
    static void Listen(int fd, int backlog = 5)
    {
        if (listen(fd, backlog) < 0)
        {
            LOG(FATAL, "socket: " + std::to_string(fd) + "listen error");
            exit(SOCK_LISTEN);
        }
    }
};