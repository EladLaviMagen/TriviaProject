#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
	Question(std::string question, std::vector<std::string> ans);
	std::vector <std::string> getPossibleAnswers();
	int getCorrectAnswerID();
	std::string getQuestion();

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;

};

