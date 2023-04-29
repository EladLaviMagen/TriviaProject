#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>
int main()
{
    std::string input = "";
    WSAInitializer wsaInit;
    Server server;
    server.run();
    while(input != "EXIT")
    {
        input = "";
        std::cin >> input;
    }
    return 0;
}