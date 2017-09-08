#pragma once

#include <map>
#include <cstdint>
#include <iostream>

enum Side{Black, White};

class Position {
public:
	uint8_t x;
	uint8_t y;
	Position(uint8_t myx, uint8_t myy) : x(myx), y(myy) {};
};

class Piece {
public:
	Side side;
	bool isKing;
	Piece(Side mySide, bool amKing = false) : side(mySide), isKing(amKing) {};
	Piece() : side(White), isKing(false) {
		std::cout << "P-100" << std::endl;
	}
};

class Board {
private:
	std::map<Position, Piece> pieces;
public:
	static Board getDefaultBoard();
	std::map<Position, Piece> getPiecesOnSide(Side);
	void placePiece(Position, Piece);
	const Piece* getPiece(Position) const;
	friend std::ostream& operator<<(std::ostream&, const Board&);
};
class Game {
	Board board;
};