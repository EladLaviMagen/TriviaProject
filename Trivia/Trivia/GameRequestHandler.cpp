#include "GameRequestHandler.h"


GameRequestHandler::GameRequestHandler(Game game, LoggedUser user, GameManager manager, RequestHandlerFactory factory) : m_game(game), m_user(user), m_gameManager(manager), m_handlerFactory(factory)
{}

bool GameRequestHandler::isRequestRelevant(RequestInfo info) 
{
	if (info.id == GETQUESTION || info.id == SUBMITANS || info.id == GETRESULTS || info.id == LEAVEGAME)
	{
		return true;
	}
	return false;
}
RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	RequestResult result;
	if (info.id == GETQUESTION)
	{
		result = getQuestion(info);
	}
	else if (info.id == SUBMITANS)
	{
		result = submitAnswer(info);
	}
	else if (info.id == GETRESULTS)
	{
		result = getGameResults(info);
	}
	else
	{
		result = leaveGame(info);
	}
	return result;
}
RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	RequestResult result;
	GetQuestionResponse res;
	Question question = m_game.getQuestionForUser(m_user);
	std::map<unsigned int, std::string> ans;
	if (question.getCorrectAnswerID() != -1)
	{
		for (int i = 0; i < 4; i++)
		{
			ans[i] = (question.getPossibleAnswers())[i];
		}
		res.answers = ans;
		res.question = question.getQuestion();
		res.status = 1;
		result.newHandler = this;
		result.response = JsonResponsePacketSerializer::serializeResponse(res);
	}
	else
	{
		result = getGameResults(info);
	}
	return result;
}
RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	RequestResult result;
	SubmitAnswerResponse res;
	SubmitAnswerRequest req = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	res.correctAnswerId = m_game.submitAnswer(m_user, req.answerId);
	res.status = 1;
	result.newHandler = this;
	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	return result;
}
RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	RequestResult result;
	GetGameResultsResponse res;
	res.results = m_game.getResults(m_user);
	res.status = STATUS_GAME_FINISHED;
	result.newHandler = this;
	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	return result;
}
RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	this->m_game.removeUser(m_user);
	if (m_game.isEmpty())
	{
		m_gameManager.deleteGame(m_game.getId());
	}
	RequestResult result;
	result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return result;
}