//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "piece.h"

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