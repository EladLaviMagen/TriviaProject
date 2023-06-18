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
    json buff;
    std::map<int, std::string> a;
    a[1] = "a";
    a[2] = "aaaaa";
    buff["chec"] = a;
    std::cout << buff.dump();
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