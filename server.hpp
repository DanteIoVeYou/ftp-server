#pragma once
#include "socket.hpp"

static const std::string SERVER_VERSION = "FTP-v0.1-copyright@abc-running on GNU Linux";
class Server
{
public:
    Server(uint16_t port = 2222) : _port(port) {}
    ~Server()
    {
        close(_listen_fd);
    }
    void Init()
    {
        _listen_fd = Socket::Create();
        Socket::Bind(_listen_fd, _port);
        LOG(INFO, "init server success...");
    }
    bool SendLocalInfo(const std::string &local_info)
    {
    }
    bool RecvID()
    {
    }
    bool SendIDValid()
    {
    }
    bool RecvPwd()
    {
    }
    bool Login()
    {
    }
    void Loop()
    {
        while (true)
        {
            Socket::Listen(_listen_fd);
            int ret = Socket::Accept(_listen_fd);
            if(ret < 0) {
                LOG(ERROR, "Listen error");
                continue;
            }
            // 发送本服务器版本信息
            SendLocalInfo(SERVER_VERSION);
            // 等待对方发起用户名验证，查询用户名
            RecvID();
            // 返回用户名的合法性
            SendIDValid();
            // 等待对方发送密码，验证密码的合法性
            RecvPwd();
            // 登录成功，等待对方操作
            Login();
        }
    }

private:
    uint16_t _port; // 绑定端口
    int _listen_fd; // 套接字
};