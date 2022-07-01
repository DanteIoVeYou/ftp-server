#include "server.hpp"

int main()
{
    Server *p = new Server;
    p->Init();
    p->Loop();
    std::cout << "server start" << std::endl;
    return 0;
}