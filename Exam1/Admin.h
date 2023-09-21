#pragma once
#include <iostream>
#include <fstream>
#include "User.h"
#include "Test.h"
#include <string>
#include <vector>
#include <set>
#include "TestedUser.h"

class User;
class Admin;
class Test;
class TestedUser;

// ������� ���������� ����� ��� ������, ������� � ������ � ���������� � ������ ������ ��� ��������� �������� � ����
inline void rightCinCheck(int& answ)
{
	do {
		std::cin >> answ;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cin >> answ;
		}
	} while (!std::cin);
}


class DataBase
{
	friend Admin;
	std::vector<Test> tests;
	std::set<TestedUser*> users;
	std::vector<std::string> sections;
public:
	// ���������� ������������ � ���� ������, ����� � ��� � � ����
	void addUser(TestedUser& us, const int key) {
		users.insert(&us);
		userToFile(us, key);
	}
	TestedUser* giveUser(const std::string log, const std::string pas);
	// ��������, �� ����� �� ����� ������������
	bool usersLoginCheck(const std::string& lig) const;
	// ��������� ���������� �������������
	const int getUsersNumber() const { return users.size(); }
	// ��������� ������� ������
	const std::vector<Test> getTests() const { return tests; }
	// ��������� ������� ������ � �������� �� ���������� ��������� ������
	const std::vector<Test> getTestsBySection(const std::string section) const;
	// ��������� ������� ���������
	const std::vector<std::string> getSections() const { return sections; }
	// ��������� ������ ���������� ������������ � ���� � ����������� ����������� ��������� ������
	void userToFile(const TestedUser& tu, const int key);
	// �������� �� ������������� ������������ � ���� ������ ��� �������� ��� � �������
	bool isUser(const std::string log,const std::string pas) const;
};

class Admin : public User
{
	int key;
	DataBase db;
	// ���� � ������������ ������� ������ �� �����
	Admin(bool);
	// ����������� ������ ������ � ���������� ������������� ������ � ����
	void reg();
public:
	// �������� ������, ������� ������������ ������������ �� ����� ������� �����
	Admin();
	// ���������� ����� ��������� � ���� ������
	void addSection();
	// "��������" �������� ������ ����� � ������������ ���� ��� ���������� � ���������
	void addTest();
	// "�������������" �������� ������ ����� � ��������� ��� ������������� � ���� ������
	void addTest(const Test& test);
	// ��������� ������� ������
	auto getTests() const { return db.tests; }
	// ��������� ������� ���������
	auto getSections() const { return db.sections; }
	// ��������� ���� ������
	DataBase& getDataBase(){ return db; }
	// ��������� ������ � ������ ������ 
	void changeMyLoginData();
	// ����� ����������� ������������ �� ��������� / ����������� ����� / ����������� ������������
	void showResults();
	// ��������� ����� ���������� (��� ���������� ������ �������������)
	const int getKey() const { return key; }
	// ��������� ������ ������������ ���� ������
	void editUser();
	// ��������� ������������� � ����
	void usersToFile();
	// �������� ���������� ������������ �� ���� ������
	void removeUser();
	// ������� ���� � ������ �����
	char* toChar(int num);
	// ��������� ��������� ���������, �������� � ���� ������ � ���� ��� ������� �����
	void sectionToFile();
	// ��������� ���� ��������� �� ���� ������ � ���� � ��������������� �������� �����
	void sectionsToFile();
	// ��������� ��������� �� ����� �������� � ���� ������
	void sectionsFromFile();
	// ��������� ���������� �����, ��������� � ���� ������ � ���� ��� ������� �����
	void testToFile();
	// ��������� ���� ������ �� ���� ������ � ���� � ��������������� �������� �����
	void testsToFile();
	// ��������� ������ �� ����� �������� � ���� ������
	void testsFromFile();
};