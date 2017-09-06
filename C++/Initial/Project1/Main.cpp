#include <iostream>
#include <string>
#include <stdlib.h>
#include "Main.h"
#include <vector>
#include <set>
#include <string>
#include <sstream>

#include "guessMyNumber.h"
#include "bankAccount.h"
#include "bankAccount.cpp"

int main() {
	BankAccount greg("Greg");
	std::vector<BankAccount> accounts;
	accounts.push_back(BankAccount("Greg"));
	accounts.push_back(BankAccount("Goob"));
	accounts.push_back(BankAccount("John"));

	for (auto const& t : accounts) {
		std::cout << t;
	}

	std::cout << greg.money;
	int x;
	std::cin >> x;
}



