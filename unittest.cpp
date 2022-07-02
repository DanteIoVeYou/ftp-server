// #include "server.hpp"
#include <iostream>
#include <filesystem>
int main()
{
    std::string buffer_cmd;
    while (true)
    {
        std::cout << "ftp>";
        fflush(stdout);
        std::string line;
        std::getline(std::cin, line);
        line += "\r\n";
        std::cout << line;
        fflush(stdout);
        buffer_cmd += line;
        if (line == "\r\n")
        {
            std::cout << "enter" << std::endl;
            break;
        }
    }
    return 0;
}
