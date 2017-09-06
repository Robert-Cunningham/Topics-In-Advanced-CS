#pragma once

#include <string>

class Person {
public:
	static std::string getRandomName();
};

class BankAccount {
public:
	int money;
	std::string name;

	BankAccount(std::string name);
};
