#include "Game.h"
int Game::id = 1;

Question Game::getQuestionForUser(LoggedUser user)
{
    return m_players[user].currentQuestion;
}

void Game::submitAnswer(LoggedUser user, unsigned int id)
{
    if (getQuestionForUser(user).getCorrectAnswerID() == id)
    {
        m_players[user].correctAnswerCount++;
    }
    else
    {
        m_players[user].wrongAnswerCount++;
    }
    int i = 0;
    for (auto it = m_questions.begin(); it != m_questions.end(); it++)
    {
        i++;
        if (it->getQuestion() == m_players[user].currentQuestion.getQuestion())
        {
            it = m_questions.end();
        }
    }
    m_players[user].currentQuestion = m_questions[i];
}

void Game::removeUser(LoggedUser user)
{
    m_players.erase(user);
}
