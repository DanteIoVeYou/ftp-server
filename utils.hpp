#pragma once
#include "log.hpp"

class Utils
{
public:
    static void Readline(int fd, std::string *line)
    {
        // Method: get\r\n
        LOG(DEBUG, *line);
        char ch = 0;
        while (true)
        {
            int s = recv(fd, &ch, 1, 0);
            std::cout << "ch: " << ch << std::endl;
            if (s < 0)
            {
                LOG(ERROR, "read line error");
                return;
            }
            if (ch == '\r')
            {
                continue;
            }
            if (ch == '\n')
            {
                break;
            }
            else
            {
                (*line) += ch;
            }
        }
        LOG(DEBUG, ((*line) + " end").c_str());
    }

    static void CutString(const std::string &line, std::string *first_string, std::string *second_string, const std::string &sep)
    {
        int pos;
        if ((pos = line.find(sep)) == std::string::npos)
        {
            LOG(ERROR, "cut string error");
            return;
        }
        (*first_string) = line.substr(0, pos);
        (*second_string) = line.substr(pos + sep.size());
    }
};
