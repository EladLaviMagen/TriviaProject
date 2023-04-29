#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
int main()
{
    WSAInitializer wsaInit;
    Server server;
    server.run();
    while(true)
    {

    }
    return 0;
}