#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager m_login, IDatabase* m_data) : m_loginManager(m_login)
{
    m_database = m_data;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this, m_loginManager);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, m_roomManager, m_StatisticsManager, *this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

