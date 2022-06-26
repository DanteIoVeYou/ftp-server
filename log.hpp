#pragma once
#include "common.hpp"
#define LOG(level, msg) Log::ShowLog(#level, msg, __FILE__, __LINE__)
enum LEVEL
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};
class Log
{
public:
    Log() {}
    ~Log() {}
    static void ShowLog(std::string level, std::string msg, std::string filename, int line)
    {
        std::cout << level << " " << Time::GetTime() << " " << msg << " " << filename << " " << line << std::endl;
    }
};
