#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(LoginManager m_login, IDatabase* m_data, RoomManager m_rooms, StatisticsManager m_statistics) : m_loginManager(m_login), m_roomManager(m_rooms), m_gameManager(GameManager(m_data))
{
    m_StatisticsManager = m_statistics;
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

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser loggedUser, Room room)
{
    return new RoomAdminRequestHandler(room, loggedUser, m_roomManager, *this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser loggedUser, Room room)
{
    return new RoomMemberRequestHandler(room, loggedUser, m_roomManager, *this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user)
{
    return new GameRequestHandler(m_gameManager.getGame(user.getUserName()),user, m_gameManager, *this);
}

GameManager& RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}

