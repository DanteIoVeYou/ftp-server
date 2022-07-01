/* This is a protocal to give messages between server and client
 * Begin *
 *
 * Method:XXX\r\n
 * Filename:XXX\r\n
 * \r\n
 * (File to Transfer)
 *
 * End *
 */
#pragma once
#include "log.hpp"
class Request
{
public:
    Request() {}
    ~Request() {}
    std::string _request_line; // 请求行 -> Method:xxx\r\n
    std::string _request_header;
};

class Response
{
public:
    Response() {}
    ~Response() {}
    std::string _method;
    std::string _filename;
    bool _hasFile;
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
    EndPointC() {}
    ~EndPointC() {}

public:
    Request _req;
    Response _resp;
};