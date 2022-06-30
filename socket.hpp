#pragma once
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
        int opt = 128;
        setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
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
    static int Accept(int fd)
    {
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        bzero(&peer, len);
        int ret = accept(fd, (sockaddr *)&peer, &len);
        return ret;
    }
    static void Connect(int fd, const std::string &ip, uint16_t port)
    {
        sockaddr_in peer;
        bzero(&peer, sizeof(peer));
        peer.sin_family = AF_INET;
        peer.sin_port = htons(port);
        peer.sin_addr.s_addr = inet_addr(ip.c_str());
        if (connect(fd, (sockaddr *)&peer, sizeof(peer)) < 0)
        {
            LOG(FATAL, "connect server error");
            exit(SOCK_CONNECT);
        }
    }
};