#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this, m_loginManager);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}
