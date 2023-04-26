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
}

player_type player::get_type() {
	return type;
}

void player::add_piece(piece *p) {
	pieces_on_board.push_back(p);
}

void player::init_pieces() {
	pieces_on_board.push_back(new king(type));
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

auto player::begin() -> decltype(pieces_on_board.begin()) {
	return pieces_on_board.begin();
}

auto player::end() -> decltype(pieces_on_board.end()) {
	return pieces_on_board.end();
}

piece *player::operator[](int index) {
	return pieces_on_board[index];
}

