//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include "queen.h"
#include "../table.h"


queen::queen(player_type p) : piece(p) {
	pair<char, char> pos;
	if (p == white) {
		set_name("♕");
		pos = pair<char, char>('D', 1);
	} else {
		set_name("♛");
		pos = pair<char, char>('D', 8);
	}
	piece::set_position(pos);
	table::get_instance().set_piece(this, pos);
}

vector<move> queen::get_possible_moves() {
	vector<move> moves = {};
	table& t = table::get_instance();
	pair<char, char> pos = get_position();
	pair<char, char> next_pos;

	// up
	for (int i = 1; i <= 8 - pos.second; ++i) {
		next_pos = pair<char, char>(pos.first, pos.second + i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down
	for (int i = 1; i <= pos.second - 1; ++i) {
		next_pos = pair<char, char>(pos.first, pos.second - i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// left
	for (int i = 1; i <= pos.first - 'A'; ++i) {
		next_pos = pair<char, char>(pos.first - i, pos.second);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// right
	for (int i = 1; i <= 'H' - pos.first; ++i) {
		next_pos = pair<char, char>(pos.first + i, pos.second);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// up left
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first - i, pos.second + i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// up right
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first + i, pos.second + i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down left
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first - i, pos.second - i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down right
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first + i, pos.second - i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	return moves;
}