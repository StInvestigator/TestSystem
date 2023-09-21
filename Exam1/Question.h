#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "Admin.h"

class Admin;

class Question
{
	friend Admin;
	std::string question;
	std::vector<std::string> possibleAnswers;
	std::list<std::string> rightAnswers;
	// �������� ������� ���� �������� ���� ��� ����������
	Question(std::string q, std::vector<std::string> pa, std::list<std::string> ra) : question{q},possibleAnswers{pa},rightAnswers{ra}{}
public:
	// "��������" �������� ������� � ������������ ���� ��� ���������� �� ���� ���������
	Question();
	// ������ ������. � ������ ����������� ������ ���������� true
	bool askQuestion();
};