#include "stdafx.h"
#include "Checkers.h"
#include <map>
#include <set>
#include <algorithm>

std::set<Board> Board::getNextStates() const {
	std::map<Position, Piece> myPieces = getPiecesOnSide(toMove);
	std::map<Position, Piece>::iterator it;
	std::set<Board> moves; //this is probably a memory leak.

	for (it = myPieces.begin(); it != myPieces.end(); it++) {
		getNextStatesWithMoveFrom(moves, it->first);
	}

	return moves;
}

std::pair<int, Move> Board::negamax(int depth, int alpha, int beta) const { //https://en.wikipedia.org/wiki/Negamax thanks for the algo reminder
	if (depth == 0) {
		return std::make_pair(getValue(), mostRecentMove);
	}
	std::set<Board> nextStates = getNextStates();

	if (nextStates.size() == 0) {
		//the current player loses.
		if (toMove == White) {
			return std::make_pair(INT_MIN, mostRecentMove);
		}
		else {
			return std::make_pair(INT_MAX, mostRecentMove);
		}
	}

	Move bestMove = Move(White, Position(77, 77), Position(77, 77));

	int best = INT_MIN; //must initialize;
	for (auto const& currentState : nextStates) {
		int val;
		Move otherMove = Move(White, Position(77, 77), Position(77, 77)); //figure out wtf is going on here;
		std::tie(val, otherMove) = currentState.negamax(depth - 1, -1 * beta, -1 * alpha);
		if (val > best) {
			best = val;
			bestMove = currentState.mostRecentMove;
		}
		best = std::max(val, best);
		alpha = std::max(alpha, val);

		if (alpha >= beta) {
			break;
		}
	}

	return std::make_pair(best, mostRecentMove);
}

int Board::getValue() const {
	return 0;
}

void Board::swapActivePlayer() {
	if (toMove == White) {
		toMove = Black;
	}
	else {
		toMove = White;
	}
}

void Board::getNextStatesWithMoveFrom(std::set<Board>& next, const Position p) const {
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
			current.swapActivePlayer();
			next.insert(current);
		} else if (endPiece->side == piece->side) {
			continue;
		} else if (endPiece->side != piece->side) {
			//Jumping code.
		}
	}
}

std::map<Position, Piece> Board::getPiecesOnSide(Side s) const {
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

	b.toMove = White;
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