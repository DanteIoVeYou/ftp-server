#pragma once
#include "log.hpp"

class Utils
{

public:
    static void Readline(int fd, std::string *line)
    {
        // Method: get\r\n
        char ch = 0;
        while (ch != '\r')
        {
            int s = recv(fd, &ch, 1, 0);
            if (s < 0)
            {
                LOG(ERROR, "read line error");
                return false;
            }
            (*line) += ch;
        }
        (*line) += '\n';
        return true;
    }

    static void CutString(const std::string &line, std::string *first_string, std::string *second_string, const std::string &sep)
    {
        int pos;
        if ((pos = line.find(sep)) == std::string::npos)
        {
            LOG(ERROR, "cut string error");
            return false;
        }
        (*first_string) = line.substr(0, pos);
        (*second_string) = line.substr(pos + sep.size());
        return true;
    }
}
