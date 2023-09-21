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
	// �����-�����������, ��� � ������������ �������� ������������� �����
	bool reminder()const;
public:
	// �������� ������������ � ����������� ��������� ��� � ���� ������ � ����
	TestedUser(DataBase& db, const int key);
	// �������� ��������� ��� ������ ���������� set � ���� ������
	bool operator<(const TestedUser& us) const ;
	// ��������� ������ ������������
	auto getLogin() const { return login; }
	// ��������� ������ ������������
	auto getPassword() const { return password; }
	// ������ ����������� ����� �� ���� ������
	void startTheTest(const DataBase& db);
	// ����������� ��� �������� �����
	void continueTheTest();
	// ���������� �������������� �����
	void endTheTest();
	// ���������� ����������� �������������� �����
	void endTheTest(const Test& t);
	// ����� ���� ����������� ���������� ������
	void showResults();
};