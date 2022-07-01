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
    std::string _method;
    std::string _filename;
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