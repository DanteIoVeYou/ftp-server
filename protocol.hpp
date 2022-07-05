/* This is a protocal to give messages between server and client
 * Begin * Packet Format
 *
 * Method:XXX\r\n
 * Filename:XXX\r\n
 * \r\n
 * (File to Transfer)
 *
 * End *
 */

/* Cmd Line Format ******
 * Method [Paras]
 *
 *
 *
 */
#pragma once
#include "log.hpp"
class Request
{
public:
    Request() {}
    ~Request() {}
    std::string _request_line;       // 请求行 -> Method:xxx\r\n
    std::string _method = "Method:"; // 方法
    std::string _request_header;
    std::string _filename = "Filename:";
    std::string _LF = LF;
};

class Response
{
public:
    Response() {}
    ~Response() {}
    std::string _method;
    std::string _filename;
    // bool _hasFile;
};

/*服务端的远端：向客户端发送报文*/
class EndPointS
{
public:
    EndPointS() {}
    ~EndPointS() {}

public:
    Request _req;
    Response _resp;
};
/*客户端的远端：向服务端发送报文*/

class EndPointC
{
public:
    EndPointC(std::string cmd_line, int sock) : _cmd_line(cmd_line), _sock(sock)
    {
        LOG(DEBUG, "create ep success");
        ParseCmdLine();
    }
    ~EndPointC() {}

private:
    void ParseCmdLine()
    {
        // 根据空格分开命令
        std::string para;
        for (int i = 0; i < _cmd_line.size(); i++)
        {
            if (_cmd_line[i] != ' ')
            {
                para += _cmd_line[i];
            }
            else
            {
                if (!para.empty())
                {
                    _cmd_paras.push_back(para);
                    para.clear();
                }
            }
        }
        if (!para.empty())
        {
            _cmd_paras.push_back(para);
        }
    }
    void Build_ls()
    {
        // 1. ls命令请求行：Method:ls\r\n
        _req._method += "ls";
        _req._method += LF;
        _req._request_line += _req._method;
        // 2. ls命令请求报头
        _req._request_header = "";
        // 3. ls命令空行
        _req._LF = LF;
        LOG(INFO, "build ls");
    }
    void Build_get()
    {
    }
    void Build_quit()
    {
    }
    void Build_put()
    {
    }
    void Build_pwd()
    {
    }

public:
    void BuildRequest()
    {
        // 根据命令的不同构建不同的请求报文结构体
        std::string method = _cmd_paras[0];
        LOG(DEBUG, "paras" + method);
        if (method == "ls")
        {
            Build_ls();
        }
        else if (method == "get")
        {
            Build_get();
        }
        else if (method == "put")
        {
            Build_put();
        }
        else if (method == "quit")
        {
            Build_quit();
        }
        else if (method == "pwd")
        {
            Build_pwd();
        }
    }

    void SendRequest()
    {
        if (!_req._request_line.empty())
        {
            send(_sock, _req._request_line.c_str(), _req._request_line.size(), 0);
            LOG(DEBUG, "request line send");
        }
        if (!_req._request_header.empty())
        {
            send(_sock, _req._request_header.c_str(), _req._request_header.size(), 0);
            LOG(DEBUG, "request header send");
        }
        if (!_req._LF.empty())
        {
            send(_sock, _req._LF.c_str(), _req._LF.size(), 0);
            LOG(DEBUG, "LF send");
        }
    }

    void RecvResponse()
    {
        std::string resp;
        char buffer[BUFFER_SIZE];
        ssize_t ss = 0;
        ss = recv(_sock, buffer, sizeof(buffer) - 1, 0);
        if (ss > 0)
        {
            buffer[ss] = 0;
        }
        std::cout << "@@@" << buffer << "@@@" << std::endl;
        // while (ss = read(_sock, buffer, sizeof(buffer) - 1) > 0)
        // {
        //     buffer[ss] = 0;
        //     resp += buffer;
        // }
        // std::cout << resp << std::endl;
    }
    void ParseResponse()
    {
    }
    void ShowResponse()
    {
    }

public:
    Request _req;
    Response _resp;
    int _sock;
    std::string _cmd_line;
    std::vector<std::string> _cmd_paras;
};