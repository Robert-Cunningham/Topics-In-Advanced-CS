// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Checkers.h"
#include <iostream>

void wait() {
	int x;
	std::cin >> x;
}

int main()
{
	Board b = Board::getDefaultBoard();
	std::cout << b << std::endl;
	wait();
    return 0;
}


