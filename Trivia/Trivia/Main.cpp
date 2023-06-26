#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>
#include <exception>

class Server;
class LoginManager;
class RequestHandlerFactory;

int main()
{
    //this is where it all began
    std::string input = "";
    WSAInitializer wsaInit;
    IDatabase* data = new SqliteDatabase();
    Server server(RequestHandlerFactory(LoginManager(data), data, StatisticsManager(data)));
    server.run();
    while(input != "EXIT")
    {
        input = "";
        std::cin >> input;
    }
    return 0;
}