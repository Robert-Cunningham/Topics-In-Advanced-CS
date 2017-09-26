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
	
	
	Game g;
	
	//g.board = fromString("2---------B------W-W--------W------------------W--------W------W-");

	//2---B-B-wb--------b-w----b---b------------------------B--b-------
	g.playGame();
	wait();
	return 0;

	//g.board = fromString("2-w-w-w-ww-w---w----w-w-wb-----w----w----b-b-b-b--b---b-bb-b-b-b-");
	std::cout << g.board << std::endl;
	//for (auto const& current : g.board.getNextStates()) {
	//	std::cout << current << std::endl;
	//}
	g.AITurn();
	std::cout << g.board << std::endl;
	wait();
	return 0;
	//std::cout << g.board.toString().c_str() << std::endl;
	//std::cout << Board::getDefaultBoard() << std::endl;
	//std::cout << fromString("2-w-w-w-ww-w-w-w--w-w-w-w----------------b-b-b-b--b-b-b-bb-b-b-b-") << std::endl;
	//std::cout << fromString("2-w-w-w-ww-w---w----w-w-wb-----w----w----b-b-b-b--b---b-bb-b-b-b-") << std::endl;
	//2-w-w-w-ww-w---w----w-w-wb-----w----w----b-b-b-b--b---b-bb-b-b-b- (why not double jump?
	//Board a = fromString("1-w-w-w-ww-w-w-w--b---w-ww-w-------------b-B-b-b--b---b-bb---b-bB");
	//Board b = fromString("1-w-w-w-ww-w-w-w--b---w-ww-w-------------b---b-b--B---b-bb-b-b-bB");

	//std::cout << a << std::endl << b << std::endl;
	//std::cout << (a < b) << std::endl;
	//wait();
	//return 0;
	//g.board.swapActivePlayer();
	//1-w-w-w-ww-w-w-w--w-w-w-w----------------b-b-b-b--b-b-b-bb-b-b-b- (default)
	//1-w-w-w-ww-w-w-w--b---w-ww-w-------------b-B-b-b--b---b-bb---b-bB (a)
	//1-w-w-w-ww-w-w-w--b---w-ww-w-------------b---b-b--B---b-bb-b-b-bB (b)


	g.board.placePiece(Position(3, 6), Piece(Black, true));
	g.board.placePiece(Position(7, 7), Piece(Black, true));
	//b.placePiece(Position(2, 2), Piece(White));
	g.board.placePiece(Position(2, 5), Piece(White));
	//g.board.placePiece(Position(0, 2), Piece(White));
	g.board.placePiece(Position(0, 3), Piece(White));
	//g.board.placePiece(Position(7, 7), Piece(White));
	std::cout << "Best Move: " << std::endl << g.board.findBestMove(5) << std::endl;
	//wait();
	g.board.removePiece(Position(7, 7));

	std::cout << "Best Move: " << std::endl << g.board.findBestMove(5) << std::endl;
	//wait();
	//return 0;
	//b.placePiece(Position(0, 2), Piece(Black));
	//b.placePiece(Position(3, 3), Piece(Black));
	//g.playGame();
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
//	for (auto const &current : g.board.getNextStates()) {
//		std::cout << current << std::endl;
//	}

	
	wait();
    return 0;
	
}


