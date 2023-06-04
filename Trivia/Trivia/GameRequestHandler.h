#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(Game game, LoggedUser user, GameManager manager, RequestHandlerFactory factory);
	virtual bool isRequestRelevant(RequestInfo) override;
	virtual RequestResult handleRequest(RequestInfo) override;
	RequestResult getQuestion(RequestInfo);
	RequestResult submitAnswer(RequestInfo);
	RequestResult getGameResults(RequestInfo);
	RequestResult leaveGame(RequestInfo);
private:
	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
};

