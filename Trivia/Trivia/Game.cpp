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
    return m_players[user.getUserName()].currentQuestion;
    timer = time(0);
}

void Game::submitAnswer(LoggedUser user, unsigned int id)
{
    
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
    
}

void Game::removeUser(LoggedUser user)
{
    m_players.erase(user.getUserName());
}
