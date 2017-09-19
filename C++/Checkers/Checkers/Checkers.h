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
public:
	friend bool operator<(const Board&, const Board&);
	static Board getDefaultBoard();
	std::set<Board*> getNextStates(Side);
	std::set<Board*> getNextStatesWithMoveFrom(const Position);
	std::map<Position, Piece> getPiecesOnSide(Side);
	void placePiece(const Position, const Piece);
	inline void removePiece(const Position);
	const Piece* getPiece(const Position&) const;
	friend std::ostream& operator<<(std::ostream&, const Board&);
};
class Game {
	Board board;
};