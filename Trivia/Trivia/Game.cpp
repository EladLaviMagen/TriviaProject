#include "Game.h"
int Game::id = 1;

Question Game::getQuestionForUser(LoggedUser user)
{
    return Question("What the hell", std::vector<std::string>());
}

void Game::submitAnswer(LoggedUser user, unsigned int id)
{
}

void Game::removeUser(LoggedUser user)
{
}
