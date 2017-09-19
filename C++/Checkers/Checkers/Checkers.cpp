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
	//std::set<Board*> next;
	//next.insert(&b);
	//b.placePiece(Position(4, 4), White);
	//b.removePiece(Position(0, 1));
	//std::set<Board*> next = b.getNextStates(White);
	//std::set<Board> next;
	//b.getNextStatesWithMoveFrom(next, Position(5, 2));
	std::set<Board> next = b.getNextStates(White);
	//std::cout << b << std::endl;
	//wait();
	//return 0;
/*
	std::map<Position, Piece> myMap = b.getPiecesOnSide(White);

	for (auto const &dank: myMap) {
		std::cout << dank.first << " " << dank.second << " " << std::endl;
	}
	
	*/
	for (auto const &current : next) {
		std::cout << "new:" << current/*.getPiece(Position(1, 1))*/ << std::endl;
	}
	
	wait();
    return 0;
	
}


