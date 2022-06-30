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
};