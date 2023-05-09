#include "SqliteDatabase.h"

const char* SqliteDatabase::DB_FILE_NAME = "DB.sqlite";
const char* SqliteDatabase::USERS_TABLE = "users:";
const char* SqliteDatabase::ID_COLUMN = "id";
const char* SqliteDatabase::PASSWORD_COLUMN = "password";
const char* SqliteDatabase::MAIL_COLUMN = "mail";
const char* SqliteDatabase::NAME_COLUMN = "username";
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
        << ID_COLUMN << " INTEGER PRIMARY KEY AUTOINCREMENT, "
        << NAME_COLUMN << " TEXT NOT NULL, "
        << PASSWORD_COLUMN << " TEXT NOT NULL, "
        << MAIL_COLUMN << " TEXT NOT NULL);";
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