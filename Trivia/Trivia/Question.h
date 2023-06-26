#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
	Question() = default;
	Question(std::string question, std::vector<std::string> ans, int id);
	std::vector <std::string> getPossibleAnswers();
	int getCorrectAnswerID();
	std::string getQuestion();

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int correctId;

};

