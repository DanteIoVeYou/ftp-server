#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
enum Sock_Execpt
{
    SOCK_CREATE,
    SOCK_BIND,
    SOCK_LISTEN,
    SOCK_CONNECT
};
class Time
{
public:
    Time() {}
    ~Time() {}
    static std::string GetTime()
    {
        time_t timestamp = time(nullptr);
        tm *timestruct = localtime(&timestamp);
        char buffer[64];
        strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timestruct);
        std::string ret(buffer);
        return ret;
    }
};
