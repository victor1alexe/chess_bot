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

board::board() : white(WHITE), black(BLACK), _backup(nullptr) {
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
	if (moves.empty()) return move::START;
    return moves.top();
}

bool board::would_be_check(move m) {
	board& b = get_instance();

	b.make_backup();
	b.make_move(m);

	piece *k = (get_piece(m.get_to())->get_type() == WHITE) ? white.get_king() : black.get_king();
	position king_pos = positions[k];

	bool would_be_in_check = false;
	position p;
	vector<piece*> pieces = {};

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first + i, king_pos.second + i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first - i, king_pos.second + i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first + i, king_pos.second - i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first - i, king_pos.second - i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first + i, king_pos.second);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first - i, king_pos.second);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first, king_pos.second + i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		p = position(king_pos.first, king_pos.second - i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	std::for_each(pieces.begin(), pieces.end(), [&](piece* p) {
		if (p->see_king()) {
			would_be_in_check = true;
		}
	});

	b.restore();
	return would_be_in_check;
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

// 	If the move puts the king in check, return false
	bool would_be_in_check = would_be_check(m);
	if (would_be_in_check) return false;

//	If the end position is empty, return true
	bool is_empty = get_piece(to) == nullptr;
	if(is_empty) return true;

//	If the end position is occupied by a piece of the same color, return false
	bool is_available = get_piece(to)->get_type() != p;
	if (!is_available) return false;

	return true;
}

bool board::is_castle_possible(player_type p_t, side s) {
	player p = (p_t == WHITE) ? white : black;
	switch (p_t) {
		case WHITE:
			switch (s) {
				case QUEEN:
					if (p.can_long_castle()) {
						piece* queen = (*this)[{'D', '1'}];
						piece* bishop = (*this)[{'C', '1'}];
						piece* knight = (*this)[{'B', '1'}];
						if (queen != nullptr && bishop != nullptr && knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E1D1"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E1C1"))) {
							restore();
							return false;
						}
						return true;
					}
					break;
				case KING:
					if (p.can_short_castle()) {
						piece* bishop = (*this)[{'F', '1'}];
						piece* knight = (*this)[{'G', '1'}];
						if (bishop != nullptr && knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E1F1"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E1G1"))) {
							restore();
							return false;
						}

						return true;
					}
					break;
				default:
					break;
			}
			break;
		case BLACK:
			switch (s) {
				case QUEEN:
					if (p.can_long_castle()) {
						piece* queen = (*this)[{'D', '8'}];
						piece* bishop = (*this)[{'C', '8'}];
						piece* knight = (*this)[{'B', '8'}];
						if (queen != nullptr && bishop != nullptr && knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E8D8"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E8C8"))) {
							restore();
							return false;
						}
						return true;
					}
					break;
				case KING:
					if (p.can_short_castle()) {
						piece* bishop = (*this)[{'F', '8'}];
						piece* knight = (*this)[{'G', '8'}];
						if (bishop != nullptr && knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E8F8"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E8G8"))) {
							restore();
							return false;
						}

						return true;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return false;
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
//			TODO: Implement castling
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

			// TODO: CASTLE

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

	him.set_in_check(attacker->see_king());
	me.set_in_check(false);
	moves.push(m);
}

map<piece*, position> board::get_positions() {
	return positions;
}

map<position, piece*> board::get_pieces() {
	return pieces;
}

stack<move> board::get_moves() {
	return moves;
}

backup::backup() {
	pieces_cp = board::get_instance().get_pieces();
	positions_cp = board::get_instance().get_positions();
	moves_cp = board::get_instance().get_moves();
	white_cp = board::get_instance().get_white();
	black_cp = board::get_instance().get_black();
}

void board::make_backup() {
	_backup = new backup();
}

void board::restore() {
	pieces = _backup->pieces_cp;
	positions = _backup->positions_cp;
	moves = _backup->moves_cp;
	white = _backup->white_cp;
	black = _backup->black_cp;
}