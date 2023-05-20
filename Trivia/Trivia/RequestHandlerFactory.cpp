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
