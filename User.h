#pragma once
#include <iostream>
#include <string>

class User
{
protected:
	std::string login;
	std::string password;
	User() : login{ "" }, password{ "" } {}
	User(std::string log, std::string pas) : login{ log }, password{pas} {}
};