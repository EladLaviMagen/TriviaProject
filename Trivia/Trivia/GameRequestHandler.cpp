#include "GameRequestHandler.h"
//
//
//GameRequestHandler::GameRequestHandler(Game game, LoggedUser user, GameManager manager, RequestHandlerFactory factory) : m_game(game), m_user(user), m_gameManager(manager), m_handlerFactory(factory)
//{}
//
//bool GameRequestHandler::isRequestRelevant(RequestInfo info) 
//{
//
//}
//RequestResult GameRequestHandler::handleRequest(RequestInfo info)
//{
//
//}
//RequestResult GameRequestHandler::getQuestion(RequestInfo info)
//{
//	RequestResult result;
//	GetQuestionResponse res;
//	Question question = m_game.getQuestionForUser(m_user);
//	std::map<int, std::string> ans;
//	for (int i = 0; i < 4; i++)
//	{
//		ans[i] = (question.getPossibleAnswers())[i];
//	}
//	res.answers;
//}
//RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
//{
//
//}
//RequestResult GameRequestHandler::getGameResults(RequestInfo info)
//{
//
//}
//RequestResult GameRequestHandler::leaveGame(RequestInfo info)
//{
//
//}