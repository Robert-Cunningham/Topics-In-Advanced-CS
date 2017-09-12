// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Checkers.h"
#include <iostream>
#include <set>

void wait() {
	int x;
	std::cin >> x;
}

int main()
{
	Board b = Board::getDefaultBoard();
	std::set<Board*> next = b.getNextStates(White);
	for (auto const& current : next) {

		std::cout << "new:" << (*current) << std::endl;
	}
	std::cout << b << std::endl;
	wait();
    return 0;
}


