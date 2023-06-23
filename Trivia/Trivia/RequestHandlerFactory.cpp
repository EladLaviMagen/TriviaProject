#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager m_login, IDatabase* m_data, StatisticsManager m_statistics) : m_loginManager(m_login)
{
    
    m_StatisticsManager = m_statistics;
    m_roomManager = new RoomManager();
    m_database = m_data;
    m_gameManager = new GameManager(m_data);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this, std::ref(m_loginManager));
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, this->getRoomManager(), m_StatisticsManager, this);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return m_StatisticsManager;
}

RoomManager* RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser loggedUser, Room room)
{
    return new RoomAdminRequestHandler(room, loggedUser, this->getRoomManager(), this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser loggedUser, Room room)
{
    return new RoomMemberRequestHandler(room, loggedUser, this->getRoomManager(), this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user)
{
    return new GameRequestHandler(m_gameManager->getGame(user.getUserName()),user, m_gameManager, this);
}

GameManager* RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}

