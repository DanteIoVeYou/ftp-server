#pragma once
#include "log.hpp"

class Utils
{
public:
    static void Readline(int fd, std::string *line)
    {
        // Method: get\r\n
        char ch = 0;
        while (true)
        {
            int s = recv(fd, &ch, 1, 0);
            printf("%d\n", ch);
            if (s == 0)
            {
                // 对端关闭连接
                std::string msg = "fd: ";
                msg += std::to_string(fd);
                msg += " closed";
                LOG(INFO, msg);
                break;
            }
            if (s < 0)
            {
                LOG(ERROR, "read line error");
                return;
            }

            else
            {
                (*line) += ch;
                if (ch == '\n')
                {
                    break;
                }
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

    static void MoveLF(std::string &line, const std::string &endstr)
    {
        line = line.substr(0, line.size() - endstr.size());
    }


};
