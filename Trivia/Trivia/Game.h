#pragma once
#include "Question.h"
#include "LoggedUser.h"
#include <map>

typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;
};

class Game
{
public:
	Game(std::vector<Question> questions, std::vector<LoggedUser> players);
	Question getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, unsigned int id);
	void removeUser(LoggedUser user);
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	unsigned int gameId;
	static int id;


};

