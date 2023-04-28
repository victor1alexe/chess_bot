//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "player.h"
#include "piece.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"

player::player(player_type type) : type(type) {
	pieces_on_board = {};
	pieces_in_hand = {};
	in_check = false;
}

player_type player::get_type() {
	return type;
}

void player::add_piece(piece *p) {
	pieces_on_board.push_back(p);
}

void player::capture_piece(piece *p) {
	pieces_in_hand.push_back(p);
}

void player::remove_piece(piece *p) {
	pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), p), pieces_on_board.end());
}

void player::place_piece(piece *p) {
	pieces_in_hand.erase(std::remove(pieces_in_hand.begin(), pieces_in_hand.end(), p), pieces_in_hand.end());
}

void player::init_pieces() {
	my_king = new king(type);
	pieces_on_board.push_back(my_king);
	pieces_on_board.push_back(new queen(type));
	pieces_on_board.push_back(new rook(type, QUEEN));
	pieces_on_board.push_back(new rook(type, KING));
	pieces_on_board.push_back(new bishop(type, QUEEN));
	pieces_on_board.push_back(new bishop(type, KING));
	pieces_on_board.push_back(new knight(type, QUEEN));
	pieces_on_board.push_back(new knight(type, KING));
	for (char i = 'A'; i <= 'H'; i++) {
		pieces_on_board.push_back(new pawn(type, i));
	}
}

void player::set_in_check(bool in_check) {
	this->in_check = in_check;
}

bool player::is_in_check() const {
	return in_check;
}

vector<move> player::get_possible_moves() const {
	vector<move> moves = {};
	for (auto piece : pieces_on_board) {
		vector<move> piece_moves = piece->get_possible_moves();
		moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
	}
	return moves;
}

auto player::begin() -> decltype(pieces_on_board.begin()) {
	return pieces_on_board.begin();
}

auto player::end() -> decltype(pieces_on_board.end()) {
	return pieces_on_board.end();
}

piece *player::operator[](int index) {
	return pieces_on_board[index];
}

piece* player::get_king() const {
	return my_king;
}