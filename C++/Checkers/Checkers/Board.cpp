#include "stdafx.h"
#include "Checkers.h"
#include <map>
#include <set>

std::set<Board> Board::getNextStates(Side toMove) {
	std::map<Position, Piece> myPieces = getPiecesOnSide(toMove);
	std::map<Position, Piece>::iterator it;
	std::set<Board> moves; //this is probably a memory leak.

	for (it = myPieces.begin(); it != myPieces.end(); it++) {
		getNextStatesWithMoveFrom(moves, it->first);
	}

	return moves;
}

void Board::getNextStatesWithMoveFrom(std::set<Board>& next, const Position p) {
	int moves[4][2] = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}; //white is the first two. black is the second two.
	const Piece* piece = getPiece(p);
	int movesToCheck = piece->isKing ? 4 : 2;
	int sideOffset = piece->side == White || piece->isKing ? 0 : 2;

	for (int i = sideOffset; i < movesToCheck + sideOffset; i++) {
		const Position endPos = Position(p.x + moves[i][0], p.y + moves[i][1]);
		if (!endPos.isValid()) {
			continue;
		}

		const Piece* endPiece = getPiece(endPos);
		if (endPiece == nullptr) {
			Board current = Board(*this);
			current.removePiece(Position(p.x, p.y));
			current.placePiece(endPos, *piece);
			next.insert(current);
		} else if (endPiece->side == piece->side) {
			continue;
		} else if (endPiece->side != piece->side) {
			//Jumping code.
		}
	}
}

std::map<Position, Piece> Board::getPiecesOnSide(Side s) {
	std::map<Position, Piece> out;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			const Piece* p = getPiece(Position(x, y));
			if (p == nullptr) {
				continue;
			}
			if (p->side == s) {
				out[Position(x, y)] = *p;
			}
		}
	}
	return out;
}

Board Board::getDefaultBoard() {
	Board b;
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

std::ostream& operator<<(std::ostream& os, const Piece& p) {
	if (p.side == White) {
		if (p.isKing) {
			os << "W";
		}
		else {
			os << "w";
		}
	}
	else {
		if (p.isKing) {
			os << "B";
		}
		else {
			os << "b";
		}
	}

	return os;
}

bool Position::isValid() const {
	return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}

std::ostream& operator<<(std::ostream& o, const Board& b) {
	o << "--------" << std::endl;
	for (int y = 7; y >= 0; y--) {
		for (int x = 0; x < 8; x++) {
			//o << "dealing with " << x << ", " << y << std::endl;
			//Position pos = Position(x, y);
			const Piece* p = b.getPiece(Position(x, y));
			if (p == nullptr) {
				o << " ";
			}
			else {
				//o << (*p) << "(<-" << x << " " << y << ") ";
				o << (*p);
			}
		}
			o << std::endl;
	}
	o << "--------" << std::endl;

	return o;
}

inline const Piece* Board::getPiece(const Position& pos) const {
	std::map<Position, Piece>::const_iterator out;
	out = pieces.find(pos);
	if (out == pieces.end()) {
		return nullptr;
	} else {
		return &(out->second);
	}
}

inline void Board::placePiece(Position pos, Piece piece) {
	pieces[pos] = piece;
}

inline void Board::removePiece(Position pos) {
	pieces.erase(pos);
}

inline bool operator<(const Position &a, const Position &b) {
	return a.x * 10 + a.y < b.x * 10 + b.y;
}

inline bool operator<(const Board& a, const Board& b) {
	return a.pieces < b.pieces;
}

bool operator<(const Piece& a, const Piece& b) {
	if (a.side == b.side) {
		if (a.isKing == b.isKing) {
			return false;
		}
		return !a.side;
	}
	return !a.isKing;
}