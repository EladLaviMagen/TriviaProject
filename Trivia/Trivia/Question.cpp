#include "Question.h"

Question::Question(std::string question, std::vector<std::string> ans, int id)
{
    m_question = question;
    m_possibleAnswers = ans;
    correctId = id;
}

std::vector<std::string> Question::getPossibleAnswers()
{
    return m_possibleAnswers;
}

int Question::getCorrectAnswerID()
{
    return correctId;
}

std::string Question::getQuestion()
{
    return m_question;
}
