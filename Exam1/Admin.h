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

// функцию используют почти все классы, поэтому я сделал её глобальной в хэдэре админа для избежания повторов в коде
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
	// Добавление пользователя в базу данных, сразу с тем и в файл
	void addUser(TestedUser& us, const int key) {
		users.insert(&us);
		userToFile(us, key);
	}
	TestedUser* giveUser(const std::string log, const std::string pas);
	// Проверка, не занят ли логин пользователя
	bool usersLoginCheck(const std::string& lig) const;
	// Получение количества пользователей
	const int getUsersNumber() const { return users.size(); }
	// Получение массива тестов
	const std::vector<Test> getTests() const { return tests; }
	// Получения массива тестов с фильтром по конкретной категории знаний
	const std::vector<Test> getTestsBySection(const std::string section) const;
	// Получение массива категорий
	const std::vector<std::string> getSections() const { return sections; }
	// Занесение одного переданого пользователя в файл с последующим шифрованием переданым ключем
	void userToFile(const TestedUser& tu, const int key);
	// Проверка на существование пользователя в базе данных без привязки его к системе
	bool isUser(const std::string log,const std::string pas) const;
};

class Admin : public User
{
	int key;
	DataBase db;
	// Вход в существующий аккаунт админа из файла
	Admin(bool);
	// Регестрация нового админа с занесением зашифрованных данных в файл
	void reg();
public:
	// Создание админа, которое перекидывает пользователя на выбор способа входа
	Admin();
	// Добавление новой категории в базу данных
	void addSection();
	// "Глубокое" создание нового теста с определением всех его параметров в программе
	void addTest();
	// "Поверхностное" создание нового теста с передачей уже существующего в базу данных
	void addTest(const Test& test);
	// Получение массива тестов
	auto getTests() const { return db.tests; }
	// Получение массива категорий
	auto getSections() const { return db.sections; }
	// Получение базы данных
	DataBase& getDataBase(){ return db; }
	// Изменение Логина и Пароля админа 
	void changeMyLoginData();
	// Показ результатов тестирований по категории / конкретному тесту / конкретному пользователю
	void showResults();
	// Получение ключа шифрования (для шифрования данных пользователей)
	const int getKey() const { return key; }
	// Изменение любого пользователя базы данных
	void editUser();
	// Занесение пользователей в файл
	void usersToFile();
	// Удаление выбранного пользователя из базы данных
	void removeUser();
	// Перевод инта в массив чаров
	char* toChar(int num);
	// Занесение последней категории, вошедшей в базу данных в файл без очистки файла
	void sectionToFile();
	// Занесение всех категорий из базы данных в файл с предварительной очисткой файла
	void sectionsToFile();
	// Получение категорий из файла напрямую в базу данных
	void sectionsFromFile();
	// Занесение последнего теста, вошедшего в базу данных в файл без очистки файла
	void testToFile();
	// Занесение всех тестов из базы данных в файл с предварительной очисткой файла
	void testsToFile();
	// Получение тестов из файла напрямую в базу данных
	void testsFromFile();
};