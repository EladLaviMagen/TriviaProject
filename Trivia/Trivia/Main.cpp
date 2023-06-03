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
    std::string input = "";
    WSAInitializer wsaInit;
    IDatabase* data = new SqliteDatabase();
    Server server(RequestHandlerFactory(LoginManager(data), data, RoomManager(), StatisticsManager(data)));
    server.run();
    while(input != "EXIT")
    {
        input = "";
        std::cin >> input;
    }
    return 0;
}