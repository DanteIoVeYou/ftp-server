#include "client.hpp"

int main()
{
    Client *cli = new Client("127.0.0.1", 8080);
    cli->Init();
    cli->Loop();
    return 0;
}