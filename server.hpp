#pragma once
#include "socket.hpp"
#include "utils.hpp"
static const std::string SERVER_VERSION = "FTP-v0.1-copyright@abc-running on GNU Linux";
static const std::string ROOTDIR = "./root/";
static const std::string LF = "\r\n";
static const int BUFFER_SIZE = 1024;
/* 命令格式
 * 1.
 * Method: ls\r\n
 * \r\n
 * 2.
 * Method: get\r\n
 * Filename: xxx
 * \r\n
 * 3.
 * Method: put\r\n
 * Filename: xxx\r\n
 * \r\n
 * file content
 */
class Server
{
public:
    Server(uint16_t port = 8080) : _port(port) {}
    ~Server()
    {
        close(_listen_fd);
    }
    static void *handler_login(void *args)
    {
        LOG(DEBUG, "handler_login");
        int fd = *(int *)(args);
        while (true)
        {
            std::string method_line;
            Utils::Readline(fd, &method_line);
            std::cout << "ms: " << method_line.size() << std::endl;
            if (method_line.size() == 0)
            {
                // 对端连接关闭
                std::cout << "kkkkkk close" << std::endl;
                break;
            }
            else
            {
                // 去掉 \r\n
                Utils::MoveLF(method_line, LF);
                LOG(DEBUG, method_line);
                std::string method;
                std::string cmd;
                Utils::CutString(method_line, &method, &cmd, ":");
                LOG(DEBUG, "method@" + method);
                LOG(DEBUG, "cmd@" + cmd);
                if (cmd == "ls")
                {
                    Cmd_ls(fd);
                }
                else if (cmd == "pwd")
                {
                    Cmd_pwd(fd);
                }
                else if (cmd == "put")
                {
                    Cmd_put(fd);
                }
                else if (cmd == "get")
                {
                    Cmd_get(fd);
                }
                else if (cmd == "quit")
                {
                    Cmd_quit(fd);
                    break;
                }
                else
                {
                    Cmd_others(fd);
                }
            }
        }
        close(fd);
        LOG(INFO, "close");
    }
    static void Cmd_ls(int fd)
    {
        std::string line;
        Utils::Readline(fd, &line);

        if (line == LF)
        {
            // 读到的只有\r\n，那么就说明当前的 ls 命令结束，socket已被读取完毕
            std::cout << "ls: \\r\\n 读取完毕" << std::endl;
        }
        std::string files;
        std::filesystem::directory_iterator fns(ROOTDIR.c_str());
        for (const auto &fn : fns)
        {
            std::string filename(fn.path().c_str());
            // file_list.push_back(filename.substr(ROOTDIR.size()));
            files += (filename.substr(ROOTDIR.size()) + LF);
        }
        if (send(fd, files.c_str(), files.size(), 0) < 0)
        {
            // Error
            return;
        }
    }
    static bool Cmd_pwd(int fd)
    {
        // TODO
    }
    static bool Cmd_put(int fd)
    {
        std::unordered_map<std::string, std::string> packet_map;
        while (true)
        {
            std::string line;
            Utils::Readline(fd, &line);
            if (line == "\r\n")
            {
                break;
            }
            std::string key;
            std::string value;
            Utils::CutString(line, &key, &value, ":");
            packet_map[key] = value;
        }
        std::string filepath = ROOTDIR + packet_map["Filename"];
        int localfile_fd = open(filepath.c_str(), O_CREAT | O_WRONLY);
        char buffer[BUFFER_SIZE] = {0};
        int size = 0;
        while (size = recv(fd, buffer, BUFFER_SIZE - 1, 0) > 0)
        {
            buffer[size] = 0;
            write(localfile_fd, buffer, size);
        }
        close(localfile_fd);
    }
    static void Cmd_get(int fd)
    {

        std::string line;
        Utils::Readline(fd, &line);
        Utils::MoveLF(line, LF);
        std::string key;
        std::string value;
        Utils::CutString(line, &key, &value, ":");
        std::string &filename = value;
        std::string filepath = ROOTDIR + filename;
        LOG(DEBUG, filepath);
        int localfile_fd = open(filepath.c_str(), O_RDONLY);
        struct stat st;
        fstat(localfile_fd, &st);
        LOG(DEBUG, std::to_string(st.st_size));
        if (sendfile(fd, localfile_fd, nullptr, st.st_size) < 0)
        {
            LOG(ERROR, "sendfile error");
        }
        Utils::Readline(fd, &line);
        if (line == LF)
        {
            std::cout << "get: \\r\\n 读取完毕" << std::endl;
        }
        close(localfile_fd);
    }
    static bool Cmd_quit(int fd)
    {
    }
    static bool Cmd_others(int fd)
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
        pthread_detach(tid);
        LOG(INFO, "get a new link");
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
            // SendLocalInfo(fd, SERVER_VERSION);
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