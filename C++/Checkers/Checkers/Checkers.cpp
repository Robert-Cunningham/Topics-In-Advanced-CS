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
	//Board b = Board::getDefaultBoard();
	//Board b;
	//b.swapActivePlayer();
	//b.placePiece(Position(4, 6), Piece(White, true));
	//b.placePiece(Position(2, 2), Piece(White));
	//b.placePiece(Position(3, 5), Piece(Black));
	//b.placePiece(Position(1, 3), Piece(Black));
	//b.placePiece(Position(0, 2), Piece(Black));
	//b.placePiece(Position(3, 3), Piece(Black));

	//std::set<Board*> next;
	//next.insert(&b);
	//b.placePiece(Position(4, 4), White);
	//b.removePiece(Position(0, 1));
	//std::set<Board*> next = b.getNextStates(White);
	//std::set<Board> next;
	//b.getNextStatesWithMoveFrom(next, Position(5, 2));
	
	//Move Test
	//std::cout << b << std::endl;

	//b.readMove();
	//Board n = b.findBestMove(6);
	//std::cout << "Best move:" << std::endl << n << std::endl;
	//std::cout << b << std::endl;
	//wait();
	//END Move Test
	//std::set<Board> next = b.getNextStates();
	//std::cout << b << std::endl << std::endl << std::endl;
	//std::cout << b << std::endl;
	//wait();
	//return 0;
/*
	std::map<Position, Piece> myMap = b.getPiecesOnSide(White);

	for (auto const &dank: myMap) {
		std::cout << dank.first << " " << dank.second << " " << std::endl;
	}
	
	*/
	//for (auto const &current : next) {
	//	std::cout << current << std::endl;
	//}

	Game g;
	g.playGame();
	
	wait();
    return 0;
	
}


