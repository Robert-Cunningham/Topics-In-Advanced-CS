#include "stdafx.h"
#include "Checkers.h"
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>

void Game::playGame() {
	std::cout << "The AI is a gentleman and allows you the honor of playing first." << std::endl;
	while (true) {
		if (board.getNextStates().size() == 0) {
			std::cout << board << std::endl << "You lose." << std::endl;
			break;
		}
		playerTurn();
		board.swapActivePlayer();
		std::cout << board.toString() << std::endl;
		if (board.getNextStates().size() == 0) {
			std::cout << "You Win." << std::endl;
			break;
		}
		AITurn();
	}
}

void Game::playerTurn() {
	std::cout << board << std::endl;
	std::cout << "Please input your selection of move." << std::endl;
	board.readMove();
	std::cout << board << std::endl;
}

void Game::AITurn() {
	std::cout << "Determining AI move..." << std::endl;
	board =*(new Board(board.findBestMove(7))); //7 causes an issue.
}

std::set<Board> Board::getNextStates() const {
	std::map<Position, Piece> myPieces = getPiecesOnSide(toMove);
	std::map<Position, Piece>::iterator it;
	std::set<Board> moves; //this is probably a memory leak.

	for (it = myPieces.begin(); it != myPieces.end(); it++) {
		getNextStatesWithMoveFrom(moves, it->first);
	}

	return moves;
}

Board Board::findBestMove(int depth) const {
	Board b;
	int val;
	//std::tie(val, b) = negamax(depth, INT_MIN, INT_MAX);
	std::tie(val, b) = minimax(depth);
	std::cout << "Minimax value: " << val << "." << std::endl;
	return b;
}

std::pair<int, Board> Board::minimax(int depth) const {
	if (toMove == White) {
		return whiteMinimax(depth, INT_MIN / 2, INT_MAX / 2);
	}
	else {
		return blackMinimax(depth, INT_MIN / 2, INT_MAX / 2);
	}
}

std::pair<int, Board> Board::whiteMinimax(int depth, int alpha, int beta) const { 
	if (depth == 0) return std::make_pair(getValue(), Board(*this));
	
	std::set<Board> nextStates = getNextStates();

	if (nextStates.size() == 0) return std::make_pair((INT_MIN/2), Board(*this));

	Board bestBoard;
	int best = INT_MIN; 
	for (auto const& currentState : nextStates) {
		int val;
		Board otherMove;

		std::tie(val, otherMove) = currentState.blackMinimax(depth - 1, alpha, beta);
		if (val > best) {
			best = val;
			bestBoard = currentState;
		}
		alpha = std::max(alpha, val);

		if (alpha >= beta) break;
	}

	return std::make_pair(best, bestBoard);
}

std::pair<int, Board> Board::blackMinimax(int depth, int alpha, int beta) const { 
	if (depth == 0) return std::make_pair(getValue(), Board(*this));
	
	std::set<Board> nextStates = getNextStates();

	if (nextStates.size() == 0) return std::make_pair((INT_MAX/2), Board(*this));

	Board bestBoard;
	int best = INT_MAX; 
	for (auto const& currentState : nextStates) {
		int val;
		Board otherMove;

		std::tie(val, otherMove) = currentState.whiteMinimax(depth - 1, alpha, beta);
		if (val < best) {
			best = val;
			bestBoard = currentState;
		}
		beta = std::min(beta, val);

		if (alpha >= beta) break;
	}

	return std::make_pair(best, bestBoard);
}
std::pair<int, Board> Board::negamax(int depth, int alpha, int beta) const { //https://en.wikipedia.org/wiki/Negamax thanks for the algo reminder
	if (depth == 0) {
		return std::make_pair(toMove * getValue(), Board(*this));
	}
	std::set<Board> nextStates = getNextStates();

	if (nextStates.size() == 0) {
		//the current player loses.
		std::cout << "someone lost." << std::endl;
		return std::make_pair(toMove * (INT_MAX/2), Board(*this));
	}

	Board bestBoard;

	int best = INT_MIN; //must initialize;
	for (auto const& currentState : nextStates) {
		int val;
		//Move otherMove = Move(White, Position(77, 77), Position(77, 77)); //figure out wtf is going on here; pretty sure this is what the next move after this one would be.
		Board otherMove;
		std::tie(val, otherMove) = currentState.negamax(depth - 1, -1 * beta, -1 * alpha);
		val = val * -1;
		//std::cout << "Observing " << std::endl << otherMove << " which has value: " << val << " at depth " << depth << std::endl;
		if (val > best) {
			best = val;
			bestBoard = currentState;
		}
		//best = std::max(val, best);
		alpha = std::max(alpha, val);

		if (alpha >= beta) {
			break;
		}
	}

	return std::make_pair(best, bestBoard);
}

void Board::readMove() {
	try {
		std::string move;
		std::cin >> move;

		std::vector<Position> moves;

		for (int currentIndex = 0; currentIndex < move.length() / 2; currentIndex++) {
			int y = move.at(currentIndex * 2) - 'a';
			int x = move.at(currentIndex * 2 + 1) - '1';
			Position p = Position(x, y);
			moves.push_back(p);

			//std::cout << p.x << "," << p.y << std::endl;
		}

		for (int currentIndex = 0; currentIndex < moves.size(); currentIndex++) {
			if (currentIndex == 0) {
				if (getPiece(moves.at(0)) == nullptr) {
					throw 99;
				}
				const Piece* myPiece = new Piece(*getPiece(moves.at(0)));
				if (myPiece == nullptr) {
					std::cout << "Illegal move." << std::endl;
				}
				else {
					removePiece(moves.at(0));
					placePiece(moves.at(moves.size() - 1), *myPiece);
				}
			}

			if (currentIndex > 0) { //check for a jump between this move and the previous one.
				int xd = moves.at(currentIndex).x - moves.at(currentIndex - 1).x;
				int yd = moves.at(currentIndex).y - moves.at(currentIndex - 1).y;

				if (abs(xd) == 2 && abs(yd) == 2) {
					Position deadPos = Position(moves.at(currentIndex - 1).x + xd / 2, moves.at(currentIndex - 1).y + yd / 2);
					removePiece(deadPos);
				}
			}
		}
	}
	catch (...) {
		std::cout << "Illegal move. Try again." << std::endl;
		readMove();
	}

}

int Board::getValue() const {
	const int KINGVAL = 20;
	const int NORMVAL = 7;
	const int PERRANK = 1;
	int blackCount = 0;
	int whiteCount = 0;
	for (auto const& x : pieces) {
		if (x.second.side == White) {
			if (x.second.isKing) whiteCount += KINGVAL;
			else whiteCount += NORMVAL + PERRANK * x.first.y;
		}
		else if (x.second.side == Black) {
			if (x.second.isKing) blackCount += KINGVAL;
			else blackCount += NORMVAL + PERRANK * (7-x.first.y);
		}
		//(x.second.side == White ? whiteCount : blackCount) += (x.second.isKing ? KINGVAL : NORMVAL) + (x.second.side == White ? x.first.y : 7-x.first.y)*PERRANK; // betcha haven't seen any code as messy as this in a while!
	}
	return whiteCount - blackCount;
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
			getNextStatesWithJumpFrom(next, p);
		}
	}
}

void Board::getNextStatesWithJumpFrom(std::set<Board>& possibilities, const Position p) const { //Add all the possible jumps from this position.
	int moves[4][2] = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1}}; //white is the first two. black is the second two.
	const Piece* piece = getPiece(p);
	int movesToCheck = piece->isKing ? 4 : 2;
	int sideOffset = piece->side == White || piece->isKing ? 0 : 2;

	for (int i = sideOffset; i < movesToCheck + sideOffset; i++) {
		const Position start = Position(p.x, p.y);
		const Position intermediate = Position(p.x + moves[i][0], p.y + moves[i][1]);
		const Position end = Position(p.x + 2*moves[i][0], p.y + 2*moves[i][1]);
		if (!end.isValid() || !intermediate.isValid()) {
			continue;
		}

		const Piece* endPiece = getPiece(end);
		const Piece* midPiece = getPiece(intermediate);

		if (endPiece==nullptr && midPiece != nullptr && midPiece->side != piece->side) {
			Board current = Board(*this);
			current.removePiece(start);
			current.removePiece(intermediate);
			current.placePiece(end, *piece);
			current.getNextStatesWithJumpFrom(possibilities, end);
			current.swapActivePlayer();
			possibilities.insert(current);
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

std::string Piece::toString() const {
	
	if (side == White) {
		if (isKing) {
			return "W";
		}
		else {
			return "w";
		}
	}
	else {
		if (isKing) {
			return "B";
		}
		else {
			return "b";
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Piece& p) {
	os << p.toString();
	return os;
}

bool Position::isValid() const {
	return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}

std::ostream& operator<<(std::ostream& o, const Board& b) {
	o << ">-1-2-3-4-5-6-7-8-<" << std::endl;
	o << ">-----------------<" << std::endl;
	for (int y = 7; y >= 0; y--) {
		o << static_cast<char>(y+'a');
		for (int x = 0; x < 8; x++) {
			//o << x << ":";
			//o << "dealing with " << x << ", " << y << std::endl;
			//Position pos = Position(x, y);
			const Piece* p = b.getPiece(Position(x, y));
			if (p == nullptr) {
				o << "| ";
			}
			else {
				//o << (*p) << "(<-" << x << " " << y << ") ";
				o << "|" << (*p);
			}
		}
		o << "|" << static_cast<char>(y + 'a') << std::endl;
		if (y != 0) {
			o << "-------------------" << std::endl;
		}
	}
	o << ">-----------------<" << std::endl;
	o << ">-1-2-3-4-5-6-7-8-<" << "[" << b.getValue() << "]"<< std::endl;

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
	if (pos.y == 7 && piece.side == White || pos.y == 0 && piece.side == Black) {
		pieces[pos] = Piece(piece.side, true);
	}
	else {
	pieces[pos] = piece;
	}
}

inline void Board::removePiece(Position pos) {
	pieces.erase(pos);
}

std::string Board::toString() const {
	std::string out;
	out.append(toMove == White ? "1" : "2");
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (getPiece(Position(x, y)) != nullptr) {
				out.append(getPiece(Position(x, y))->toString());
			}
			else {
				out.append("-");
			}
		}
	}
	return out;
}

Board fromString(std::string in) {
	Board b;
	int counter = 0;
	b.toMove = (in.at(0) == '1' ? White : Black);
	counter++;
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (in.at(counter) != '-') {
				char p = in.at(counter);
				Piece piece;
				if (p == 'W') piece = Piece(White, true);
				if (p == 'B') piece = Piece(Black, true);
				if (p == 'w') piece = Piece(White, false);
				if (p == 'b') piece = Piece(Black, false);
				
				b.placePiece(Position(x, y), piece);
			}
			counter++;
		}
	}
	return b;
}

inline bool operator<(const Position &a, const Position &b) {
	return a.x * 10 + a.y < b.x * 10 + b.y;
}

inline bool operator<(const Board& a, const Board& b) {
	//std::cout << "Comparing..." << a.toString().c_str() << std::endl << "and" << std::endl << b.toString().c_str() << std::endl;
	return a.pieces < b.pieces;
}

bool operator<(const Piece& a, const Piece& b) {
	if (a.side == b.side) {
		if (a.isKing == b.isKing) {
			return false;
		}
		return !a.isKing;
	}
	return !a.side;
}

std::ostream& operator<<(std::ostream& os, const Move& a) {
	os << "[" << a.before << " -> " << a.after << "]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Position& a) {
	os << a.x << "," << a.y;
	return os;
}