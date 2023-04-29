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
#include <iostream>

using std::cout, std::endl;

player::player(player_type type) : type(type), in_check(false), long_castle(true), short_castle(true) {
	pieces_on_board = {};
	pieces_in_hand = {};
}

player_type player::get_type() {
	return type;
}

void player::add_piece(piece *p) {
	pieces_on_board.push_back(p);
}

void player::set_short_castle(bool short_castle) {
    player::short_castle = short_castle;
}

void player::set_long_castle(bool long_castle) {
    player::long_castle = long_castle;
}

void player::capture_piece(piece *p) {
    if (p->is_promoted()) {
        p = new pawn(p->get_type(), 'A');
    }
//     p->set_type(type);
    pieces_in_hand.push_back(p);
}

void player::remove_piece(piece *p) {
	pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), p), pieces_on_board.end());
}

void player::place_piece(piece *p) {
	pieces_in_hand.erase(std::remove(pieces_in_hand.begin(), pieces_in_hand.end(), p), pieces_in_hand.end());
}

bool player::can_long_castle() const {
	return long_castle;
}

bool player::can_short_castle() const {
	return short_castle;
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

vector<piece*> player::get_pieces_in_hand() const {
    return pieces_in_hand;
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