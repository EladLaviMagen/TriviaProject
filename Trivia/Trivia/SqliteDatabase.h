#pragma once
#include "IDatabase.h"
#include <sstream>
#include"MyException.h"
class SqliteDatabase : IDatabase
{
public:
	SqliteDatabase();
	virtual bool open() override;
	virtual void close() override;
	virtual bool doesUserExist(std::string name) override;
	virtual bool doesPasswordMatch(std::string name, std::string password) override;
	virtual void addNewUser(std::string name, std::string password, std::string mail) override;
	
private:
	static int passwordMatch(void* data, int argc, char** argv, char** azColName);
	static int userExist(void* data, int argc, char** argv, char** azColName);
	void sqlRequest(const std::stringstream& sql, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
	void sqlRequest(const char* sql, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);
	void build();
	static const char* DB_FILE_NAME;
	static const char* USERS_TABLE;
	static const char* ID_COLUMN;
	static const char* PASSWORD_COLUMN;
	static const char* MAIL_COLUMN;
	static const char* NAME_COLUMN;
	sqlite3* _db;
};

