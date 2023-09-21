#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Question.h"
#include "Admin.h"

class Admin;
class Question;



class TestAtributes
{
public:
	std::string title;
	std::string section;
	TestAtributes() : title{ "" }, section{ "" } {}
	TestAtributes(std::string tle, std::string sec) : title{ tle }, section{ sec } {}
};


class Test; 

class Result
{
	friend Admin;
	friend Test;
	int numberOfQuestions;
	float grade;
	float percentage;
	int rightAnswers;
	TestAtributes atributes;

public:
	Result() :grade{ 0 }, percentage{ 0 }, rightAnswers{ 0 } {}
	Result(std::string tle, std::string sec) : atributes(tle,sec), grade{ 0 }, percentage{ 0 }, rightAnswers{ 0 } {}
	void calculateResults(const int& questionsNum);
	void showResults();
};



class Test
{
	friend Admin;
	std::vector<Question> questions;
	int currentPosition;
	Result currentResult;
	TestAtributes atributes;
public:
	// "Глубокое" создание теста с определением всех его параметров по ходу программы
	Test() :currentPosition{ 0 }, currentResult(), atributes() {}
	// Создание теста путём передачи всех его параметром, помимо вопросов
	Test(std::string tle, std::string sec) : currentPosition{ 0 }, currentResult(tle, sec), atributes(tle, sec){}
	// Создание теста путём передачи всех его параметром
	Test(std::string tle, std::string sec, std::vector<Question> q);
	// Добавить к тесту вопрос
	void addQuestion();
	// Получить категорию теста
	const std::string getSection() const { return atributes.section; }
	// Получить название теста
	const std::string getTitle() const { return atributes.title; }
	// Получить текущий результат теста
	const Result getResult() const { return currentResult; }
	// Получить число вопросов теста
	const int getQuestionsNumber() const { return questions.size(); }
	// Начать тест
	bool startTheTest();
	// Проверка тестов на равенство
	bool operator==(const Test& t) { if (atributes.section == t.atributes.section && 
		atributes.title == t.atributes.title && questions.size()==t.questions.size()) return true; else return false; }
};