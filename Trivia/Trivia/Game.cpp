#include "Game.h"
int Game::id = 1;

Game::Game(std::vector<Question> questions, std::vector<LoggedUser> players, int qtime)
{
    m_questions = questions;
    GameData start(m_questions[0], 0, 0, 0 );
    for (int i = 0; i < players.size(); i++)
    {
        m_players[players[i].getUserName()] = start;
    }
    timer = time(0);
    gameId = id;
    id++;
    _time = qtime;
}

Question Game::getQuestionForUser(LoggedUser user)
{
    timer = time(0);
    return m_players[user.getUserName()].currentQuestion;
}

int Game::submitAnswer(LoggedUser user, unsigned int id)
{
 
    int right = getQuestionForUser(user).getCorrectAnswerID();
    if (getQuestionForUser(user).getCorrectAnswerID() == id)
    {
        m_players[user.getUserName()].correctAnswerCount++;
    }
    else
    {
        m_players[user.getUserName()].wrongAnswerCount++;
    }
    int i = 0;
    for (auto it = m_questions.begin(); it != m_questions.end(); it++)
    {
        i++;
        if (it->getQuestion() == m_players[user.getUserName()].currentQuestion.getQuestion())
        {
            it = m_questions.end();
        }
    }
    if (i == m_questions.size())
    {
        m_players[user.getUserName()].currentQuestion = Question("fake", std::vector <std::string>(), -1);
    }
    else
    {
        m_players[user.getUserName()].currentQuestion = m_questions[i];
    }
    while (difftime(time(0), timer) < (double)_time)
    {}
    return right;
}

std::vector<PlayerResults> Game::getResults(LoggedUser user)
{
    GameData data;
    PlayerResults results;
    std::vector<PlayerResults> vec;
    if (m_players.size() != 0)
    {
        for (auto it = m_players.begin(); it != m_players.end(); it++)
        {
            data = it->second;
            results.username = it->first;
            results.averageAnswerTime = data.averageAnswerTime / m_questions.size();
            results.correctAnswerCount = data.correctAnswerCount;
            results.answerTimeout = 0;
            vec.push_back(results);
        }
    }
    return vec;

    
    
}

std::map<std::string, GameData> Game::getPlayers()
{
    return m_players;
}

void Game::removeUser(LoggedUser user)
{
    m_players.erase(user.getUserName());
}

bool Game::isEmpty()
{
    return m_players.size() == 0;
}

unsigned int Game::getId()
{
    return this->gameId;
}
