#include "Game.h"
int Game::id = 1;

Game::Game(std::vector<Question>* questions, std::vector<LoggedUser>* players, int qtime)
{
    m_questions = questions;
    auto it = m_questions->begin();
    m_players = new std::map<std::string, GameData>();
    GameData start(*it, 0, 0, 0 );
    for (auto i = players->begin(); i != players->end(); i++)
    {
        std::pair<std::string, GameData> p = std::pair<std::string, GameData>(i->getUserName(), start);
        m_players->insert(p);
    }
    timer = time(0);
    gameId = id;
    id++;
    _time = qtime;
}

Question Game::getQuestionForUser(LoggedUser user)
{
    timer = time(0);
    return (*m_players)[user.getUserName()].currentQuestion;
}

int Game::submitAnswer(LoggedUser user, unsigned int id)
{
 
    int right = getQuestionForUser(user).getCorrectAnswerID();
    if (getQuestionForUser(user).getCorrectAnswerID() == id)
    {
        (*m_players)[user.getUserName()].correctAnswerCount++;
    }
    else
    {
        (*m_players)[user.getUserName()].wrongAnswerCount++;
    }
    int i = 0;
    for (auto it = m_questions->begin(); it != m_questions->end(); it++)
    {
        i++;
        if (it->getQuestion() == (*m_players)[user.getUserName()].currentQuestion.getQuestion())
        {
            it = m_questions->end();
        }
    }
    (*m_players)[user.getUserName()].currentQuestion = (*m_questions)[i];
    (*m_players)[user.getUserName()].averageAnswerTime += difftime(time(0), timer);
    while (difftime(time(0), timer) < _time)
    {}
    return right;
}

std::vector<PlayerResults> Game::getResults(LoggedUser user)
{
    GameData data;
    PlayerResults results;
    std::vector<PlayerResults> vec;
    if (m_players->size() != 0)
    {
        for (auto it = m_players->begin(); it != m_players->end(); it++)
        {
            data = it->second;
            results.username = it->first;
            results.averageAnswerTime = data.averageAnswerTime / (float)m_questions->size();
            results.correctAnswerCount = data.correctAnswerCount;
            results.answerTimeout = 0;
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
