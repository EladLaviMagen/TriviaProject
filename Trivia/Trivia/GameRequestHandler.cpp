#include "GameRequestHandler.h"

std::mutex GameRequestHandler::check;
//C'tor
GameRequestHandler::GameRequestHandler(Game* game, LoggedUser user, GameManager* manager, RequestHandlerFactory* factory) : m_game(game), m_user(user)
{
	m_gameManager = manager;
	m_handlerFactory = factory;
}

bool GameRequestHandler::isRequestRelevant(RequestInfo info) 
{
	if (info.id == GETQUESTION || info.id == SUBMITANS || info.id == GETRESULTS || info.id == LEAVEGAME)//checking if the request is relevant
	{
		return true;
	}
	return false;
}
RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	//giving the right handling for the request
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
	Question question = m_game->getQuestionForUser(m_user);//getting the current question
	std::map<unsigned int, std::string> ans;
	result.newHandler = this;
	if (question.getCorrectAnswerID() == -1)//showing end
	{
		res.status = 2;

	}
	else
	{
		for (int i = 0; i < 4; i++)//getting all possible answers
		{
			ans[i] = (question.getPossibleAnswers())[i];
		}
		res.answers = ans;//ading response the answers and the question
		res.question = question.getQuestion();
		res.status = 1;

	}
	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	return result;
}
RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	RequestResult result;
	SubmitAnswerResponse res;
	SubmitAnswerRequest req = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
	res.correctAnswerId = m_game->submitAnswer(m_user, req.answerId);//getting the right answer id so the client would know 
	res.status = 1;
	result.newHandler = this;
	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	return result;
}
RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	RequestResult result;
	GetGameResultsResponse res;
	res.results = m_game->getResults(m_user);//getting the results and sending a msg
	res.status = STATUS_GAME_FINISHED;
	result.newHandler = this;
	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	return result;
}

/*Tried to update and it didn't work :(
* std::vector<PlayerResults> vec = m_game->getResults(m_user);
* for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].username == m_user.getUserName())
		{
			m_gameManager->updateScores(vec[i]);
		}
	}
*/

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	this->m_game->removeUser(m_user);//if the persong leaving the game fromm the client than remove from game
	if (m_game->isEmpty())//if the game is empty (there are no users in it) removing it from the vector
	{
		m_gameManager->deleteGame(m_game->getId());
	}
	RequestResult result;
	result.newHandler = m_handlerFactory->createMenuRequestHandler(m_user);//returning him to main
	LeaveGameResponse res;
	res.status = 1;
	result.response = JsonResponsePacketSerializer::serializeResponse(res);
	return result;
}