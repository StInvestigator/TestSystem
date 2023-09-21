#include "Question.h"
#include <Algorithm>
#include <numeric>

Question::Question()
{
	using std::cout;
	using std::cin;
	std::string posAnsw;
	int answ=1;
	int count = 0;
	cout << "\nEnter the question:\n";
	std::getline(std::cin >> std::ws, question); 
	do
	{
		cout << "\nEnter the possible answer #"  << ++count << ":\n";
		std::getline(std::cin >> std::ws, posAnsw);
		possibleAnswers.push_back(posAnsw);
		if (count > 1) {
			cout << "\nContinue to add possible answers?\n1 - Continue\n0 - Stop\n";
			do {
				rightCinCheck(answ);
			} while (answ < 0 || answ > 1);
		}
	} while (answ && possibleAnswers.size()<9);
	std::vector<std::string> tmp = possibleAnswers;
	do
	{
	count = 0;
	cout << "---------------\n"; 
	for (auto& el : tmp) {
			cout << "Answer #" << ++count << "\t" << el << std::endl;
	}
	cout << "---------------\n";
		cout << "\nMark the number of the RIGHT answer:\n";
		do {
			rightCinCheck(answ);
		} while (answ>count || answ<=0); 
		rightAnswers.push_back(tmp.at(answ - 1));
		tmp.erase(tmp.begin() + (answ - 1));
		cout << "\nAre these all correct answers?\n1 - No, continue adding right answers\n0 - Yes, stop marking right answers\n";
		do {
			rightCinCheck(answ);
			if (answ == 1 && tmp.size() == 0) {
				cout << "\nYou out of options\n";
				answ = 0;
			}
		} while (answ < 0 || answ > 1);
	} while (answ);
	rightAnswers.unique();
}

bool Question::askQuestion()
{
	using std::cout;
	using std::cin;
	std::list<std::string> answers;
	int count;
	int answ;
	std::vector<std::string> tmp = possibleAnswers;
	do
	{
		count = 0;
		cout << question << std::endl;
		cout << "---------------\n";
		for (auto& el : tmp) {
			cout << "Answer #" << ++count << "\t" << el << std::endl;
		cout << "---------------\n";
		}
		cout << "\nMark the number of the RIGHT answer:\n";
		do {
			rightCinCheck(answ);
		} while (answ > count || answ <= 0);
		answers.push_back(tmp.at(answ-1));
		tmp.erase(tmp.begin() + (answ - 1));
		cout << "\nAre these all correct answers?\n2 - I want to uncheck my previous mark \n1 - No, continue marking right answers\n0 - Yes, stop marking right answers\n";
		do {
			rightCinCheck(answ);
			if (answ == 1 && tmp.size() == 0) {
				cout << "\nYou out of options. Ending the question...\n";
				answ = 0;
			}
		} while (answ < 0 || answ > 2);
		if (answ == 2) {
			do
			{
				if (answers.size() >= 1) {
					tmp.push_back(*answers.rbegin());
					answers.erase(--answers.end());
					cout << "\nNow your marked answers looks like this:\n";
					count = 0;
					std::cout << "---------------\n";
					for (auto& el : answers) {
						cout << "Answer #" << ++count << "\t" << el << std::endl;
						std::cout << "---------------\n";
					}
					cout << "\nWhat should we do next?\n2 - Uncheck one more\n1 - Continue answering\n0 - Stop answering\n";
					do
					{
						rightCinCheck(answ);
					} while (answ > 2 || answ < 0);
				}
				else {
					cout << "\nYou have no marked answers!!\n";
					answ = 1;
				}
			} while (answ==2);
		}
	} while (answ);
	answers.unique();
	rightAnswers.sort();
	answers.sort();
	return (rightAnswers.size()==answers.size() && rightAnswers == answers);
}