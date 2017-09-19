#pragma once

#include <map>
#include <cstdint>
#include <iostream>
#include <set>

enum Side{Black, White};

class Position {
public:
	int x;
	int y;
	Position(int myx, int myy) : x(myx), y(myy) {};
	bool isValid() const;
};

class Piece {
public:
	Side side;
	bool isKing;
	Piece(Side mySide, bool amKing = false) : side(mySide), isKing(amKing) {};
	Piece() : side(White), isKing(false) {
		std::cout << "P-100" << std::endl;
	};
	friend std::ostream& operator<<(std::ostream&, const Piece&);
};

class Board {
private:
	std::map<Position, Piece> pieces;
	Side toMove;
public:
	friend bool operator<(const Board&, const Board&);
	static Board getDefaultBoard();
	std::set<Board> getNextStates() const;
	void getNextStatesWithMoveFrom(std::set<Board>& results, const Position) const;
	std::map<Position, Piece> getPiecesOnSide(Side) const;
	void placePiece(const Position, const Piece);
	inline void removePiece(const Position);
	const Piece* getPiece(const Position&) const;
	friend std::ostream& operator<<(std::ostream&, const Board&);
	int getValue() const;
	int negamax(int, int, int) const;
	void swapToMove();
};
class Game {
	Board board;
};