#include "stdafx.h"
#include "Checkers.h"

Board Board::getDefaultBoard() {
	Board b = Board();
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 8; x++) {
			if ((x + y) % 2 == 1) {
				b.placePiece(Position(x, y), Piece(White)); //Huh, can implicitly convert from White to Piece(White).
			}
		}
	}
	for (int y = 5; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((x + y) % 2 == 1) {
				b.placePiece(Position(x, y), Piece(Black));
			}
		}
	}
	return b;
}

std::ostream& operator<<(std::ostream& o, const Board& b) {
	for (int y = 7; y >= 0; y--) {
		for (int x = 0; x < 8; x++) {
			const Piece* p = b.getPiece(Position(x, y));
			if (p == nullptr) {
				o << " ";
			} else if (p->side == White) {
				o << "w";
			} else if (p->side == Black) {
					o << "b";
			} 
		}
		o << std::endl;
	}

	return o;
}

const Piece* Board::getPiece(Position pos) const {
	std::map<Position, Piece>::const_iterator out = pieces.find(pos);
	if (out == pieces.end()) {
		return nullptr;
	} else {
		return &((*out).second);
	}
}

void Board::placePiece(Position pos, Piece piece) {
	pieces[pos] = piece;
}

inline bool operator<(const Position &a, const Position &b) {
	return a.x * 10 + a.y < b.x * 10 + b.y;
}