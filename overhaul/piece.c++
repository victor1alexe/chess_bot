//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "piece.h"
#include "board.h"
#include "pieces/king.h"
#include <iostream>
using std::cout, std::endl;

void piece::set_default_position(position position) {
	default_position = position;
}

position piece::get_default_position() {
	return default_position;
}

piece::piece(player_type type) {
	this->type = type;
	default_position = OUT;
}

player_type piece::get_type() {
	return type;
}

string piece::to_string(style style) {
	return "";
}

vector<move> piece::get_possible_moves() { return {}; }

string to_string(char c) {
	return string(1, c);
}

string to_string(position p) {
	return "" + to_string(p.first) + to_string(p.second);
}

bool piece::would_be_in_check(move m) {
	board& board = board::get_instance();

	position pos = m.get_from();
	position next_pos = m.get_to();

	return board.is_valid_move(move(pos, next_pos))
			&& board[next_pos] != nullptr
			&& board[next_pos]->get_type() != get_type()
			&& typeid(board[next_pos]) == typeid(king);
}

bool piece::see_king() { return false; };