#pragma once
#include "IDatabase.h"
#include <sstream>
#include <mutex>
#include"MyException.h"
class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	virtual bool open() override;
	virtual void close() override;
	virtual bool doesUserExist(std::string name) override;
	virtual bool doesPasswordMatch(std::string name, std::string password) override;
	virtual void addNewUser(std::string name, std::string password, std::string mail) override;
	virtual std::vector<Question> getQuestions(int numOf) override;
	virtual float getPlayerAverageAnswerTime(std::string name) override;
	virtual int getNumOfCorrectAnswer(std::string name) override;
	virtual int getNumOfTotalAnswers(std::string name) override;
	virtual int getNumOfPlayerGames(std::string name) override;
	virtual int getPlayerScore(std::string name) override;
	virtual std::vector<std::string> getHighScores() override;
	
private:
	static int passwordMatch(void* data, int argc, char** argv, char** azColName);
	static int userExist(void* data, int argc, char** argv, char** azColName);
	static int sqlGetQuestions(void* data, int argc, char** argv, char** azColName);
	static int getAverage(void* data, int argc, char** argv, char** azColName);
	static int getCorrects(void* data, int argc, char** argv, char** azColName);
	static int getTotal(void* data, int argc, char** argv, char** azColName);
	static int getScore(void* data, int argc, char** argv, char** azColName);
	static int getGames(void* data, int argc, char** argv, char** azColName);
	static int getHighestScores(void* data, int argc, char** argv, char** azColName);
	void sqlRequest(const std::stringstream& sql, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
	void sqlRequest(const char* sql, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);

	void build();
	static const char* DB_FILE_NAME;
	static const char* USERS_TABLE;
	static const char* PASSWORD_COLUMN;
	static const char* MAIL_COLUMN;
	static const char* NAME_COLUMN;
	static const char* QUESTIONS_TABLE;
	static const char* QUESTION_COLUMN;
	static const char* CORRECT_ANSWER_COLUMN;
	static const char* ANSWER1_COLUMN;
	static const char* ANSWER2_COLUMN;
	static const char* ANSWER3_COLUMN;
	static const char* STATISTICS_TABLE;
	static const char* TIME_COLUMN;
	static const char* RIGHT_ANS_COLUMN;
	static const char* ANSWERS_COLUMN;
	static const char* GAMES_COLUMN;
	static const char* SCORE_COLUMN;
	static std::mutex users;
	sqlite3* _db;
};

