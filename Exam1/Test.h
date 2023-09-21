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
	// "��������" �������� ����� � ������������ ���� ��� ���������� �� ���� ���������
	Test() :currentPosition{ 0 }, currentResult(), atributes() {}
	// �������� ����� ���� �������� ���� ��� ����������, ������ ��������
	Test(std::string tle, std::string sec) : currentPosition{ 0 }, currentResult(tle, sec), atributes(tle, sec){}
	// �������� ����� ���� �������� ���� ��� ����������
	Test(std::string tle, std::string sec, std::vector<Question> q);
	// �������� � ����� ������
	void addQuestion();
	// �������� ��������� �����
	const std::string getSection() const { return atributes.section; }
	// �������� �������� �����
	const std::string getTitle() const { return atributes.title; }
	// �������� ������� ��������� �����
	const Result getResult() const { return currentResult; }
	// �������� ����� �������� �����
	const int getQuestionsNumber() const { return questions.size(); }
	// ������ ����
	bool startTheTest();
	// �������� ������ �� ���������
	bool operator==(const Test& t) { if (atributes.section == t.atributes.section && 
		atributes.title == t.atributes.title && questions.size()==t.questions.size()) return true; else return false; }
};