#include "SqliteDatabase.h"
#include <algorithm>
#include <random>
#include <chrono> 

std::mutex SqliteDatabase::users_lock;
std::mutex SqliteDatabase::score_lock;
const char* SqliteDatabase::DB_FILE_NAME = "DB.sqlite";
const char* SqliteDatabase::USERS_TABLE = "users";
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
    //Checking if the user exists
    std::stringstream sql;
    sql << "SELECT * FROM " << USERS_TABLE << " WHERE "
        << NAME_COLUMN << " = '" << name << "';";
    {
        std::lock_guard<std::mutex> locker(users_lock);
        sqlRequest(sql, SqliteDatabase::userExist, &answer);
    }
    
    return answer == 1;
}

bool SqliteDatabase::doesPasswordMatch(std::string name, std::string password)
{
    //Checking if password matches
    std::string answer = password;
    std::stringstream sql;
    sql << "SELECT password FROM " << USERS_TABLE << " WHERE "
        << NAME_COLUMN << " = '" << name << "';";
    {
        std::lock_guard<std::mutex> locker(users_lock);
        sqlRequest(sql, SqliteDatabase::passwordMatch, &answer);
    }
    if (answer == "1")
    {
        return false;
    }
    return true;
}

void SqliteDatabase::addNewUser(std::string name, std::string password, std::string mail)
{
    //Adding user into the users and statistics table
    std::stringstream sql;
    sql << "INSERT INTO " << USERS_TABLE
    << " ( " << NAME_COLUMN << ", " << PASSWORD_COLUMN << ", " << MAIL_COLUMN << " ) VALUES (" << " '" << name << "', '" << password << "', '" << mail << "' );";
    {
        std::lock_guard<std::mutex> locker(users_lock);
        sqlRequest(sql);
    }
    sql.str();
    sql << "INSERT INTO " << STATISTICS_TABLE
    << " ( " << NAME_COLUMN << ", " << TIME_COLUMN << ", " << RIGHT_ANS_COLUMN << ", " << ANSWERS_COLUMN << ", " << GAMES_COLUMN << " ) VALUES (" << " '" << name << "', " << 0 << ", " << 0 << ", " << 0 << ", " << 0 << " );";
    {
        std::lock_guard<std::mutex> locker(users_lock);
        sqlRequest(sql);
    }
  
   
}

std::vector<Question>* SqliteDatabase::getQuestions(int numOf)
{
    //Getting the number of questions requested
    std::vector<Question>* questionList = new std::vector<Question>();
    std::stringstream sql;
    sql << "SELECT * FROM " << QUESTIONS_TABLE << " LIMIT " << numOf << ";";
    sqlRequest(sql, SqliteDatabase::sqlGetQuestions, &questionList);
    return questionList;
}

float SqliteDatabase::getPlayerAverageAnswerTime(std::string name)
{
    //Getting average answer time
    float average = 0.0;
    std::stringstream sql;
    
    sql << "SELECT * FROM " << STATISTICS_TABLE << " WHERE " << NAME_COLUMN << " = '" << name << "';";
    sqlRequest(sql, SqliteDatabase::getAverage, &average);
    return average;
}

int SqliteDatabase::getNumOfCorrectAnswer(std::string name)
{
    int corrects = 0;
    std::stringstream sql;

    sql << "SELECT * FROM " << STATISTICS_TABLE << " WHERE " << NAME_COLUMN << " = '" << name << "';";
    sqlRequest(sql, SqliteDatabase::getCorrects, &corrects);
    return corrects;
}

int SqliteDatabase::getNumOfTotalAnswers(std::string name)
{
    int total = 0;
    std::stringstream sql;
    sql << "SELECT * FROM " << STATISTICS_TABLE << " WHERE " << NAME_COLUMN << " = '" << name << "';";
    sqlRequest(sql, SqliteDatabase::getTotal, &total);
    return total;
}

int SqliteDatabase::getNumOfPlayerGames(std::string name)
{
    int games = 0;
    std::stringstream sql;
    sql << "SELECT * FROM " << STATISTICS_TABLE << " WHERE " << NAME_COLUMN << " = '" << name << "';";
    sqlRequest(sql, SqliteDatabase::getGames, &games);
    return games;
}

int SqliteDatabase::getPlayerScore(std::string name)
{
    return -1;
    //Really didn't know what to do here
}

std::vector<std::string> SqliteDatabase::getHighScores()
{
    //Ordering stats by number of correct answers and returning the results as a string vector in this format:
    //username - number of right answers
    std::vector<std::string> highestScorers;
    std::stringstream sql;
    sql << "SELECT * FROM " << STATISTICS_TABLE << " ORDER BY " << RIGHT_ANS_COLUMN << " DESC LIMIT 5;";
    sqlRequest(sql, SqliteDatabase::getHighestScores, &highestScorers);
    return highestScorers;
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
    sql << "CREATE TABLE " << USERS_TABLE << "("
        << NAME_COLUMN << " KEY TEXT NOT NULL, "
        << PASSWORD_COLUMN << " TEXT NOT NULL, "
        << MAIL_COLUMN << " TEXT NOT NULL);";
    sqlite3_exec(_db, sql.str().c_str(), nullptr, nullptr, &error);
    //This is a reset, it simply deletes all the previous strings that were inserted to it
    sql.str("");
    sql << "CREATE TABLE " << QUESTIONS_TABLE << "("
        << QUESTION_COLUMN << " KEY TEXT NOT NULL, "
        << CORRECT_ANSWER_COLUMN << " TEXT NOT NULL, "
        << ANSWER1_COLUMN << " TEXT NOT NULL, "
        << ANSWER2_COLUMN << " TEXT NOT NULL, "
        << ANSWER3_COLUMN << " TEXT NOT NULL);";
        sqlite3_exec(_db, sql.str().c_str(), nullptr, nullptr, &error);
        sql.str("");
        //q1
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'Whats the name of the cup that Lightening McQueen is racing for ? '" << ", " << "'Piston Cup'" << ", " << "'You did what in your cup'" << ", " << "'Racing cup'" << ", " << "'Shield cup'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q2
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'Whos the voice of Lightening McQueen?'" << ", " << "'Owen Wilson'" << ", " << "'Liam Hemsworth'" << ", " << "'Changing Tatum'" << ", " << "'Tom Hanks'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q3
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'What year was the Cars movie released?'" << ", " << "'2006'" << ", " << "'2004'" << ", " << "'2010'" << ", " << "'2008'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q4
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'Say my name'" << ", " << "'Heisenburg'" << ", " << "'JESSE!'" << ", " << "'My name is Gustavo'" << ", " << "'Waltuh'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q5
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'What is Lightening McQueens racing number?'" << ", " << "'95'" << ", " << "'94'" << ", " << "'65'" << ", " << "'59'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q6
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'In the movie which racing team did Lightening McQueen want to join?'" << ", " << "'Dinoco'" << ", " << "'Rusteeze'" << ", " << "'Dinosaur'" << ", " << "'Dinococo'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q7
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'What did Lightning McQueen have to fix to be allowed to leave Radiator Springs?'" << ", " << "'the road'" << ", " << "'the tower'" << ", " << "'the stadium'" << ", " << "'the ramp'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q8
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'what else was doc called?'" << ", " << "'hudson hornet'" << ", " << "'mater'" << ", " << "'dale'" << ", " << "'rpm'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q9
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'Who was lizzuy married to?'" << ", " << "'stanley'" << ", " << "'mack'" << ", " << "'sherrif'" << ", " << "'mater'" << "); ";
        sqlRequest(sql);
        sql.str("");
        //q10
        sql << "INSERT INTO " << QUESTIONS_TABLE << " ( " << QUESTION_COLUMN << ", " << CORRECT_ANSWER_COLUMN << ", " << ANSWER1_COLUMN << ", " << ANSWER2_COLUMN << ", " << ANSWER3_COLUMN
            << " ) VALUES (" << "'When cars 3 came out?'" << ", " << "'june 16 2017'" << ", " << "'july 4 2020'" << ", " << "'august 17 2017'" << ", " << "'june 2 2018'" << "); ";
        sqlRequest(sql);
        sql.str("");


    
    //This is a reset, it simply deletes all the previous strings that were inserted to it
    sql.str("");
    sql << "CREATE TABLE " << STATISTICS_TABLE << "("
        << NAME_COLUMN << " KEY TEXT NOT NULL, "
        << TIME_COLUMN << " FLOAT NOT NULL, "
        << RIGHT_ANS_COLUMN << " INTEGER NOT NULL, "
        << ANSWERS_COLUMN << " INTEGER NOT NULL, "
        << GAMES_COLUMN << " INTEGER NOT NULL);";
    sqlite3_exec(_db, sql.str().c_str(), nullptr, nullptr, &error);
    //This is a reset, it simply deletes all the previous strings that were inserted to it
    sql.str("");
}

void SqliteDatabase::updateScores(PlayerResults data)
{
    //This doesn't work, however it is supposed to update the user statistics and change them according to the most recent results given
    std::stringstream sql;
    sql << "UPDATE " << STATISTICS_TABLE << " SET " << NAME_COLUMN << "='" << data.username << "', " << TIME_COLUMN << "=" << (getPlayerAverageAnswerTime(data.username) * getNumOfTotalAnswers(data.username) + (data.averageAnswerTime * (data.correctAnswerCount + data.answerTimeout))) / (float)(getNumOfTotalAnswers(data.username) + data.correctAnswerCount + data.answerTimeout) << ", " << RIGHT_ANS_COLUMN << "=" << getNumOfCorrectAnswer(data.username) + data.correctAnswerCount << ", " << ANSWERS_COLUMN << "=" << getNumOfTotalAnswers(data.username) + data.correctAnswerCount + data.answerTimeout << ", " << GAMES_COLUMN << "=" << getNumOfPlayerGames(data.username) + 1 << " WHERE " << NAME_COLUMN << "='" << data.username << "';";
    sqlRequest(sql);
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
    std::vector<Question>** vec = (std::vector<Question>**)data;
    std::vector<std::string> ans;
    for (int i = 1; i < argc; i++)
    {
        ans.push_back(argv[i]);
    }
    //Shuffling them
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(ans.begin(), ans.end(), std::default_random_engine(seed));
    int correct = -1;
    for (int i = 0; i < ans.size(); i++)
    {
        if (ans[i] == argv[1])
        {
            correct = i;
        }
    }
    //Creating question and adding it to vector
    (*vec)->push_back(Question(argv[0], ans, correct));
    return 0;
}

int SqliteDatabase::getAverage(void* data, int argc, char** argv, char** azColName)
{
    //Gets the average
    float* average = (float*)data;
    for (int i = 0; i < argc; i++)
    {
        if (azColName[i] == TIME_COLUMN)
        {
            *average = std::stof(argv[i]);
        }

    }

    return 0;
}

int SqliteDatabase::getCorrects(void* data, int argc, char** argv, char** azColName)
{
    //Gets the correct amount of ans
    int* num = (int*)data;
    for (int i = 0; i < argc; i++)
    {
        if (azColName[i] == RIGHT_ANS_COLUMN)
        {
            *num = std::stoi(argv[i]);
        }
    }
    return 0;
}

int SqliteDatabase::getTotal(void* data, int argc, char** argv, char** azColName)
{
    //Unreal
    int* num = (int*)data;
    for (int i = 0; i < argc; i++)
    {
        if (azColName[i] == ANSWERS_COLUMN)
        {
            *num = std::stoi(argv[i]);
        }
    }
    return 0;
}

int SqliteDatabase::getScore(void* data, int argc, char** argv, char** azColName)
{
    //Getting number of games
    int* num = (int*)data;
    for (int i = 0; i < argc; i++)
    {
        if (azColName[i] == SCORE_COLUMN)
        {
            *num = std::stoi(argv[i]);
        }
    }
    return 0;
}

int SqliteDatabase::getGames(void* data, int argc, char** argv, char** azColName)
{
    //Getting number of games
    int* num = (int*)data;
    for (int i = 0; i < argc; i++)
    {
        if (azColName[i] == GAMES_COLUMN)
        {
            *num = std::stoi(argv[i]);
        }
    }
    return 0;
}

int SqliteDatabase::getHighestScores(void* data, int argc, char** argv, char** azColName)
{
    //Sets highest scores in the format I showed in the function
    std::vector<std::string>* vec = (std::vector<std::string>*)data;
    std::string stat = argv[0];
    stat += '-';
    stat += argv[2];
    vec->push_back(stat);
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