#pragma once
#include <list>
#include "Admin.h"

class User;
class Admin;
class DataBase;
class Test;
class Result;

class TestedUser : public User
{
	friend Admin;
	friend DataBase;
	std::string fullName;
	std::string adress;
	long long phoneNumber;
	std::vector<Test> ongoingTests;
	std::list<Result> myResults;
	TestedUser(std::string log, std::string pas) : User(log, pas) {}
	// ћетод-напоминалка, что у пользовател€ остались незавершенные тесты
	bool reminder()const;
public:
	// —оздание пользовател€ и последующее занесение его в базу данных и файл
	TestedUser(DataBase& db, const int key);
	// ќператор сравнени€ дл€ работы контейнера set в базе данных
	bool operator<(const TestedUser& us) const ;
	// ѕолучение логина пользовател€
	auto getLogin() const { return login; }
	// ѕолучение парол€ пользовател€
	auto getPassword() const { return password; }
	// Ќачало прохождени€ теста из базы данных
	void startTheTest(const DataBase& db);
	// ѕродолжение уже начатого теста
	void continueTheTest();
	// «авершение незавершенного теста
	void endTheTest();
	// «авершение конкретного незавершенного теста
	void endTheTest(const Test& t);
	// ¬ывод всех результатов пройденных тестов
	void showResults();
};