#include "Game.h"
int Game::id = 1;
//C'tor
Game::Game(std::vector<Question>* questions, std::vector<LoggedUser>* players, int qtime)
{
    m_questions = questions;
    auto it = m_questions->begin();//getting the first question
    m_players = new std::map<std::string, GameData>();
    GameData start(*it, 0, 0, 0 );
    for (auto i = players->begin(); i != players->end(); i++)//getting all users in game
    {
        std::pair<std::string, GameData> p = std::pair<std::string, GameData>(i->getUserName(), start);
        m_players->insert(p);
    }
    timer = time(0); // starting time
    gameId = id;//adding all needed info
    id++;
    _time = qtime;
}


Question Game::getQuestionForUser(LoggedUser user)
{
    timer = time(0);
    return (*m_players)[user.getUserName()].currentQuestion;//getting the current question
}

int Game::submitAnswer(LoggedUser user, unsigned int id)
{
    int right = (*m_players)[user.getUserName()].currentQuestion.getCorrectAnswerID();//getting the question correct answer id
    if (right == id)//checking if he is right if he is the adding to count
    {
        (*m_players)[user.getUserName()].correctAnswerCount++;
    }
    else//if he is wrong then adding to wrong answers count
    {
        (*m_players)[user.getUserName()].wrongAnswerCount++;
    }
    int i = 0;
    for (auto it = m_questions->begin(); it != m_questions->end(); it++)//getting next question
    {
        i++;
        if (it->getQuestion() == (*m_players)[user.getUserName()].currentQuestion.getQuestion())
        {
            break;//break when we getting to the question
        }
    }
    if (i != m_questions->size())//if we didn't finished all question
    {
        (*m_players)[user.getUserName()].currentQuestion = (*m_questions)[i];
    }
    else//if we finished all question
    {
        (*m_players)[user.getUserName()].currentQuestion = Question("finish", std::vector<std::string>(), 5);
    }
    (*m_players)[user.getUserName()].averageAnswerTime += difftime(time(0), timer);//getting time he answered
    while (difftime(time(0), timer) < _time)//getting through all the time
    {}
    return right;//return the right answer
}

std::vector<PlayerResults> Game::getResults(LoggedUser user)
{
    GameData data;
    PlayerResults results;
    std::vector<PlayerResults> vec;
    
    if (m_players->size() != 0)//if there are mem
    {
        bool checker = true;
        while (checker)//checking if all finished the questions
        {
            checker = false;
            for (auto it = m_players->begin(); it != m_players->end(); it++)
            {
                if (it->second.currentQuestion.getQuestion() != "finish")
                {
                    checker = true;
                }
            }
        }
        
        for (auto it = m_players->begin(); it != m_players->end(); it++)//adding the player results
        {
            data = it->second;
            results.username = it->first;
            results.averageAnswerTime = data.averageAnswerTime / (float)m_questions->size();
            results.correctAnswerCount = data.correctAnswerCount;
            results.answerTimeout = data.wrongAnswerCount;
            vec.push_back(results);
        }
    }
    return vec;
}

std::map<std::string, GameData>* Game::getPlayers()
{
    return m_players;
}

void Game::removeUser(LoggedUser user)
{
    m_players->erase(user.getUserName());
}

bool Game::isEmpty()
{
    return m_players->size() == 0;
}

unsigned int Game::getId()
{
    return this->gameId;
}
