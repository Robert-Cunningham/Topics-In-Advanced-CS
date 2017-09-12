#include "stdafx.h"
#include "Checkers.h"
#include <map>
#include <set>

std::set<Board*> Board::getNextStates(Side toMove) {
	std::map<Position, Piece> myPieces = getPiecesOnSide(toMove);
	std::map<Position, Piece>::iterator it;
	std::set<Board*> moves;

	for (it = myPieces.begin(); it != myPieces.end(); it++) {
		std::set<Board*> newMoves = getNextStatesWithMoveFrom(it->first);
		moves.insert(newMoves.begin(), newMoves.end());
	}

	return moves;
}

std::set<Board*> Board::getNextStatesWithMoveFrom(const Position p) {
	int moves[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	std::set<Board*> next;
	const Piece* piece = getPiece(p);
	int movesToCheck = piece->isKing ? 4 : 2;

	for (int i = 0; i < movesToCheck; i++) {
		const Position endPos = Position(p.x + moves[i][0], p.y + moves[i][1]);
		const Piece* endPiece = getPiece(endPos);
		if (endPiece == nullptr) {
			Board current = Board(*this);
			removePiece(endPos);
			placePiece(endPos, *piece);
			next.insert(&current);
		} else if (endPiece->side == piece->side) {
			continue;
		} else if (endPiece->side != piece->side) {
			//Jumping code.
		}
	}
	return next;
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
			o << "dealing with " << x << ", " << y << std::endl;
			const Position pos = Position(x, y);
			const Piece* p = b.getPiece(pos);
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

inline Piece* Board::getPiece(Position pos) const {
	std::map<Position, Piece>::iterator out = pieces.find(pos);
	if (out == pieces.end()) {
		return nullptr;
	} else {
		return &((*out).second);
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