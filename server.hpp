#pragma once
#include "socket.hpp"

static const std::string SERVER_VERSION = "FTP-v0.1-copyright@abc-running on GNU Linux";
static const std::string ROOTDIR = "./root/";
class Server
{
public:
    Server(uint16_t port = 2222) : _port(port) {}
    ~Server()
    {
        close(_listen_fd);
    }
    static void *handler_login(void *args)
    {
        pthread_detach(pthread_self()); // 线程分离
        int fd = *(int *)(args);
        while (true)
        {
            char buffer[1024];
            ssize_t cmd_size = recv(fd, buffer, sizeof(buffer) - 1, 0);
            if (cmd_size < 0)
            {
            }
            else
            {
                buffer[cmd_size] = 0;
                std::string cmd = buffer;
                LOG(DEBUG, cmd);

                if (cmd == "ls")
                {
                    Ls();
                }
                else if (cmd == "pwd")
                {
                    Pwd();
                }
                else if (cmd == "put")
                {
                    Put();
                }
                else if (cmd == "get")
                {
                    Get();
                }
                else if (cmd == "quit")
                {
                    Quit();
                    break;
                }
                else
                {
                    Others();
                }
            }
        }
        close(fd);
    }
    static bool Ls()
    {
        // std::vector<std::string> file_list;
        std::filesystem::directory_iterator fns(ROOTDIR.c_str());
        for (const auto &fn : fns)
        {
            std::string filename(fn.path().c_str());
            // file_list.push_back(filename.substr(ROOTDIR.size()));
            std::cout << filename.substr(ROOTDIR.size()) << std::endl;
        }
    }
    static bool Pwd()
    {
    }
    static bool Put()
    {
    }
    static bool Get()
    {
    }
    static bool Quit()
    {
    }
    static bool Others()
    {
    }
    void Init()
    {
        _listen_fd = Socket::Create();
        Socket::Bind(_listen_fd, _port);
        LOG(INFO, "init server success...");
    }
    bool SendLocalInfo(int fd, const std::string &local_info)
    {
        ssize_t ret = send(fd, local_info.c_str(), local_info.size(), 0);
        if (ret != local_info.size())
        {
            LOG(ERROR, "send local info error, " + std::to_string(ret) + "bytes have been sent\n");
        }
    }
    bool RecvID(int fd)
    {
        // std::string buffer;
        // recv(fd, buffer, sizeof(buffer) - 1, 0);
    }
    bool SendIDValid()
    {
    }
    bool RecvPwd()
    {
    }
    bool Login(int fd)
    {
        pthread_t tid;
        pthread_create(&tid, nullptr, handler_login, (void *)&fd);
        // 登陆成功
    }
    void Loop()
    {
        while (true)
        {
            Socket::Listen(_listen_fd);
            int fd = Socket::Accept(_listen_fd);
            if (fd < 0)
            {
                LOG(ERROR, "Listen error");
                continue;
            }
            // 发送本服务器版本信息
            SendLocalInfo(fd, SERVER_VERSION);
            // 等待对方发起用户名验证，查询用户名
            // RecvID();
            // 返回用户名的合法性
            // SendIDValid();
            // 等待对方发送密码，验证密码的合法性
            // RecvPwd();
            // 登录成功，等待对方操作
            Login(fd);
        }
    }

private:
    uint16_t _port; // 绑定端口
    int _listen_fd; // 套接字
};