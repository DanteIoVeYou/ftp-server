#pragma once

#include "socket.hpp"
#include "protocol.hpp"
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
        /********************/
        /* No Encapsulation */
        /********************/
        // while (true)
        // {
        //     std::cout << client_cmd_prompt;
        //     fflush(stdout);
        //     // char buffer_cmd[1024];
        //     // ssize_t size = read(0, buffer_cmd, sizeof(buffer_cmd) - 1);
        //     std::string buffer_cmd;
        //     while (true)
        //     {
        //         std::string line;
        //         std::getline(std::cin, line);
        //         line += "\r\n";
        //         buffer_cmd += line;
        //         if (line == "\r\n")
        //         {
        //             break;
        //         }
        //     }
        //     int s = send(_fd, buffer_cmd.c_str(), buffer_cmd.size(), 0);
        //     LOG(INFO, "cmd send" + std::to_string(s));
        //     char buffer1[1024];
        //     int ss = recv(_fd, buffer1, sizeof(buffer1) - 1, 0);
        //     buffer1[ss] = 0;
        //     std::cout << buffer1 << std::endl;
        // }
        /********************/
        /* Encapsulation */
        /********************/

        while (true)
        {
            std::cout << client_cmd_prompt;
            fflush(stdout);
            std::string cmd;
            std::getline(std::cin, cmd);
            EndPointC *ep = new EndPointC(cmd, _fd);
            ep->BuildRequest();
            ep->SendRequest();
            ep->RecvResponse();
            ep->ParseResponse();
            ep->ShowResponse();
            delete ep;
        }
    }

private:
    std::string _ip;
    uint16_t _port;
    int _fd;
};