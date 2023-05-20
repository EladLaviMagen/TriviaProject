#include "SqliteDatabase.h"

const char* SqliteDatabase::DB_FILE_NAME = "DB.sqlite";
const char* SqliteDatabase::USERS_TABLE = "users:";
const char* SqliteDatabase::PASSWORD_COLUMN = "password";
const char* SqliteDatabase::MAIL_COLUMN = "mail";
const char* SqliteDatabase::NAME_COLUMN = "username";
const char* SqliteDatabase::QUESTIONS_TABLE = "questions";
const char* SqliteDatabase::QUESTION_COLUMN = "question";
const char* SqliteDatabase::CORRECT_ANSWER_COLUMN = "answer";
const char* SqliteDatabase::ANSWER1_COLUMN = "fake1";
const char* SqliteDatabase::ANSWER2_COLUMN = "fake2";
const char* SqliteDatabase::ANSWER3_COLUMN = "fake3";
const char* SqliteDatabase::STATISTICS_TABLE = "statistics";
const char* SqliteDatabase::TIME_COLUMN = "time";
const char* SqliteDatabase::RIGHT_ANS_COLUMN = "rights";
const char* SqliteDatabase::ANSWERS_COLUMN = "ans";
const char* SqliteDatabase::GAMES_COLUMN = "games";
const char* SqliteDatabase::SCORE_COLUMN = "score";

/*
* C'tor
*/
SqliteDatabase::SqliteDatabase() : IDatabase()
{
    //Checking if database exists
   // if not exists - create new database
    bool notExists = _access(DB_FILE_NAME, 0);

    if (!open())
        throw MyException("Can't connect to sql DB.");

    if (notExists)
        build();

}
bool SqliteDatabase::open()
{
	return sqlite3_open(DB_FILE_NAME, &_db) == SQLITE_OK;
}


void SqliteDatabase::close()
{
    sqlite3_close(_db);
    _db = nullptr;
}

bool SqliteDatabase::doesUserExist(std::string name)
{
    int answer = 0;
    std::stringstream sql;
    sql << "SELECT * FROM " << USERS_TABLE << " WHERE "
        << NAME_COLUMN << " = '" << name << "';";
    sqlRequest(sql, SqliteDatabase::userExist, &answer);
    return answer == 1;
}

bool SqliteDatabase::doesPasswordMatch(std::string name, std::string password)
{
    std::string answer = password;
    std::stringstream sql;
    sql << "SELECT password FROM " << USERS_TABLE << " WHERE "
        << NAME_COLUMN << " = '" << name << "';";
    sqlRequest(sql, SqliteDatabase::passwordMatch, &answer);
    if (answer == "1")
    {
        return false;
    }
    return true;
}

void SqliteDatabase::addNewUser(std::string name, std::string password, std::string mail)
{
    std::stringstream sql;
    sql << "INSERT INTO " << USERS_TABLE
        << " ( " << NAME_COLUMN << ", " << PASSWORD_COLUMN << ", " << MAIL_COLUMN << " ) VALUES (" << " '" << name << "', '" << password << "', '" << mail << "' );";
    sqlRequest(sql);
}

std::list<std::string> SqliteDatabase::getQuestions(int numOf)
{
    std::list<std::string> questionList;
    std::stringstream sql;
    sql << "SELECT * FROM " << QUESTIONS_TABLE << " LIMIT " << numOf << ";";
    sqlRequest(sql, SqliteDatabase::sqlGetQuestions, &questionList);
    return questionList;
}

/*
* Function builds a new database
* Input : None
* Output : None
*/
void SqliteDatabase::build()
{
    //Preparations
    char* error = nullptr;
    std::stringstream sql;
    sql << "CREATE TABLE " <<  USERS_TABLE << "("
        << NAME_COLUMN << "PRIMARY KEY TEXT NOT NULL, "
        << PASSWORD_COLUMN << " TEXT NOT NULL, "
        << MAIL_COLUMN << " TEXT NOT NULL);";
    sqlite3_exec(_db, sql.str().c_str(), nullptr, nullptr, &error);
    //This is a reset, it simply deletes all the previous strings that were inserted to it
    sql.str("");
    sql << "CREATE TABLE " << QUESTIONS_TABLE << "("
        << QUESTION_COLUMN << "PRIMARY KEY TEXT NOT NULL, "
        << CORRECT_ANSWER_COLUMN << " TEXT NOT NULL, "
        << ANSWER1_COLUMN << " TEXT NOT NULL, "
        << ANSWER2_COLUMN << " TEXT NOT NULL, "
        << ANSWER3_COLUMN << " TEXT NOT NULL);";
    sqlite3_exec(_db, sql.str().c_str(), nullptr, nullptr, &error);
    //This is a reset, it simply deletes all the previous strings that were inserted to it
    sql.str("");
    sql << "CREATE TABLE " << STATISTICS_TABLE << "("
        << NAME_COLUMN << "PRIMARY KEY TEXT NOT NULL, "
        << TIME_COLUMN << " FLOAT NOT NULL, "
        << RIGHT_ANS_COLUMN << " INTEGER NOT NULL, "
        << ANSWERS_COLUMN << " INTEGER NOT NULL, "
        << SCORE_COLUMN << " INTEGER NOT NULL, "
        << GAMES_COLUMN << " INTEGER NOT NULL);";
    sqlite3_exec(_db, sql.str().c_str(), nullptr, nullptr, &error);
    //This is a reset, it simply deletes all the previous strings that were inserted to it
    sql.str("");
}

void SqliteDatabase::sqlRequest(const char* sql, int(*callback)(void*, int, char**, char**), void* data)
{
    char* errMsg = nullptr;
    if (sqlite3_exec(_db, sql, callback, data, &errMsg) == SQLITE_OK)
        std::cout << "did it\n";
    else
        throw MyException("cant do that");
}

void SqliteDatabase::sqlRequest(const std::stringstream& sql, int(*callback)(void*, int, char**, char**), void* data)
{
    sqlRequest(sql.str().c_str(), callback, data);
}

int SqliteDatabase::userExist(void* data, int argc, char** argv, char** azColName)
{
    //Takes ID and inputs it into pointer
    int* id = (int*)data;
    *id = 1;
    return 0;
}

int SqliteDatabase::sqlGetQuestions(void* data, int argc, char** argv, char** azColName)
{
    //Takes ID and inputs it into pointer
    std::list<std::string>* vec = (std::list<std::string>*)data;
    vec->push_back(argv[0]);
    return 0;
}

int SqliteDatabase::passwordMatch(void* data, int argc, char** argv, char** azColName)
{
    //This function is a double edged sword, it counts the amount of rows it found, making it both a count and an "exist" type function
    std::string* ptr = (std::string*)data;
    if (argv[0] != *ptr)
    {
        *ptr = "1";
    }
    return 0;
}