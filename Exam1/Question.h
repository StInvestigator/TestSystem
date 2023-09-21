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
	// Создание вопроса путём передачи всех его параметров
	Question(std::string q, std::vector<std::string> pa, std::list<std::string> ra) : question{q},possibleAnswers{pa},rightAnswers{ra}{}
public:
	// "Глубокое" создание вопроса с определением всех его параметров по ходу программы
	Question();
	// Задать вопрос. В случае правильного ответа возвращает true
	bool askQuestion();
};