//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include <iostream>
#include "pieces/king.h"
#include "board.h"

using std::cout, std::endl;
using position = pair<char, char>;

board *board::instance = new board();

board& board::get_instance() {
	return *instance;
}

board::board() : white(WHITE), black(BLACK){
	reset();
}

position board::get_position(piece *piece) {
	return positions[piece];
}

piece *board::get_piece(position position) {
	if (pieces.find(position) == pieces.end()) {
		return nullptr;
	}
	return pieces[position];
}

map<position, piece*> board::get_pieces() {
    return pieces;
}

void board::display() const {
	cout << "\u250F\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2533"
	     << "\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2533\u2501\u2501\u2501\u2513"
		 << endl;
	for (char i = '8'; i >= '1'; i--) {
		for (char j = 'A'; j <= 'H'; j++) {
			position pos = position(j, i);
			if (pieces.find(pos) == pieces.end()) {
				cout << "\u2503   ";
			} else {
				cout << "\u2503 " << pieces.at(pos)->to_string(DEBUG) << ' ';
			}
		}
		cout << "\u2503" << endl;
		if (i != '1')
			cout << "\u2523\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u254B"
			     << "\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u254B\u2501\u2501\u2501\u252B"
				 << endl;
	}
	cout << "\u2517\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u253B"
	     << "\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u253B\u2501\u2501\u2501\u251B"
		 << endl;
}

position& board::operator[](piece* piece) {
	if (positions.find(piece) == positions.end()) {
		return OUT;
	}
	return positions[piece];
}

piece* board::operator[](position position) {
	if (pieces.find(position) == pieces.end()) {
		return nullptr;
	}
	return pieces[position];
}

void board::reset() {
	pieces = map<position, piece*>();
	positions = map<piece*, position>();

	white.init_pieces();
	black.init_pieces();

	for (auto& piece : white) {
		pieces[piece->get_default_position()] = piece;
		positions[piece] = piece->get_default_position();
	}

	for (auto& piece : black) {
		pieces[piece->get_default_position()] = piece;
		positions[piece] = piece->get_default_position();
	}
}

bool board::is_in_bounds(position position) {
	return position.first >= 'A' && position.first <= 'H' && position.second >= '1' && position.second <= '8';
}

const player& board::get_white() const {
	return white;
}

const player& board::get_black() const {
	return black;
}

const move& board::get_last_move() const {
	if (moves.empty()) return move(OUT, OUT);
    return moves.top();
}

bool board::is_valid_move(move m) {
//	Get start and end positions
	const position to = m.get_to();
	const position from = m.get_from();

//	Get current player at start position
	player_type p = get_piece(from)->get_type();

//	If the end position is out of bounds, return false
	bool in_bounds = is_in_bounds(to);
	if (!in_bounds) return false;

//	If the end position is empty, return true
	bool is_empty = get_piece(to) == nullptr;
	if(is_empty) return true;

//	If the end position is occupied by a piece of the same color, return false
	bool is_available = get_piece(to)->get_type() != p;
	if (!is_available) return false;

//	TODO: check if the move would put the king in check
// 	If the move would put the king in check, return false
	bool would_be_in_check = false;

	return !would_be_in_check;
}

void board::make_move(move m) {
	const position to = m.get_to();
	const position from = m.get_from();

	piece* attacker = get_piece(from);;
	piece* captured = nullptr;

	player& me = attacker->get_type() == WHITE ? white : black;
	player& him = attacker->get_type() == WHITE ? black : white;



	switch (m.get_special()) {
		case SHORT_CASTLE:

			break;
		case LONG_CASTLE:

			break;
		case EN_PASSANT:

			if (me.get_type() == WHITE)
				captured = get_piece(position(to.first - 1, from.second));
			else
				captured = get_piece(position(to.first + 1, from.second));

			me.capture_piece(captured);
			him.remove_piece(captured);
			pieces.erase(to);
			positions.erase(captured);

			pieces.erase(from);
			positions.erase(attacker);

			pieces[to] = attacker;
			positions[attacker] = to;
			break;

		case PROMOTION:

			break;
		default:
			captured = get_piece(to);

			if (typeid(attacker) == typeid(king)) {
				dynamic_cast<king*>(attacker)->set_short_castle(false);
				dynamic_cast<king*>(attacker)->set_long_castle(false);
			}

			if (captured != nullptr) {
				me.capture_piece(captured);
				him.remove_piece(captured);
				pieces.erase(to);
				positions.erase(captured);
			}
			pieces.erase(from);
			positions.erase(attacker);

			pieces[to] = attacker;
			positions[attacker] = to;
			break;
	}

	if (attacker->see_king())
		cout << "CHECK" << endl;

	him.set_in_check(attacker->see_king());
	moves.push(m);
}