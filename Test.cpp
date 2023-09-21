#include <iostream>
#include "Test.h"

Test::Test(std::string tle, std::string sec, std::vector<Question> q): currentPosition{0}, currentResult(tle,sec),atributes(tle,sec)
{
	for (auto& el : q) {
		questions.push_back(el);
	}
}

bool Test::startTheTest()
{
	if (questions.size()) {
		int answ;
		for (currentPosition;;currentPosition++) {
			if (currentPosition >= (questions.size())) {
				currentResult.calculateResults(questions.size());
				return 1;
			}
			std::cout << "\nWant to postpone the test until later?\n1 - No, continue passing\n0 - Yes, stop for now\n";
			do
			{
				rightCinCheck(answ);
			} while (answ > 1 || answ < 0);
			if (answ == 1) {
				std::cout << "\nQuestion " << currentPosition+1 << "# ";
				currentResult.rightAnswers += questions.at(currentPosition).askQuestion();
			}
			else if (answ == 0) {
				currentResult.calculateResults(questions.size());
				return 0;
			}
		}
	}
	else {
		std::cout << "\nError! There is no questions!\n";
	}
	return 0;
}

void Test::addQuestion()
{
	questions.push_back(Question());
}

void Result::calculateResults(const int& questionsNum)
{
	if (questionsNum > 0) {
		numberOfQuestions = questionsNum;
		percentage = static_cast<float>(rightAnswers) / numberOfQuestions;
		grade = percentage * 12;
		percentage *= 100;
	}
	else {
		std::cout << "\nCant devide by zero!\n";
	}
}

void Result::showResults()
{	
	std::cout.precision(3);
	std::cout << "\nResults of the test \"" << atributes.title << "\":\nSection - " << atributes.section << "\nGrade - " << grade << " / 12\nPercentage of right answers - " 
			  << percentage << "%\nNumber of right answers - " << rightAnswers << "/" << numberOfQuestions << std::endl;
}