#pragma once
#include <iostream>
#include <io.h>
#include <list>
#include <vector>
#include "sqlite3.h"
#include "Question.h"

class Question;

class IDatabase
{
public:
	virtual bool open() = 0;
	virtual void close() = 0;
	virtual bool doesUserExist(std::string name) = 0;
	virtual bool doesPasswordMatch(std::string name, std::string password) = 0;
	virtual void addNewUser(std::string name, std::string password, std::string mail) = 0;
	virtual std::vector<Question>* getQuestions(int numOf) = 0;
	virtual float getPlayerAverageAnswerTime(std::string name) = 0;
	virtual int getNumOfCorrectAnswer(std::string name) = 0;
	virtual int getNumOfTotalAnswers(std::string name) = 0;
	virtual int getNumOfPlayerGames(std::string name) = 0;
	virtual int getPlayerScore(std::string name) = 0;
	virtual std::vector<std::string> getHighScores() = 0;
};