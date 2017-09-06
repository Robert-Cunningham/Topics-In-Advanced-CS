#include <string>
#include <iostream>
#include "bankAccount.h"

std::string Person::getRandomName() {
	return "Bill";
}

std::ostream &operator<<(std::ostream &os, BankAccount const &ba) {
	os << ba.name << " with " << ba.money << std::endl;
	return os;
}

BankAccount::BankAccount(std::string myname) : name(myname), money(10) {}