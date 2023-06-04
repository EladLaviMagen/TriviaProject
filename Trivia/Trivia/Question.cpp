#include "Question.h"

Question::Question(std::string question, std::vector<std::string> ans)
{
    m_question = question;
    m_possibleAnswers = ans;
}

std::vector<std::string> Question::getPossibleAnswers()
{
    return m_possibleAnswers;
}

int Question::getCorrectAnswerID()
{
    return 0;
}

std::string Question::getQuestion()
{
    return m_question;
}
