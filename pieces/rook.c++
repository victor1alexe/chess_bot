//
// Created by Eduard Andrei Radu on 21.04.2023.
//
#include "rook.h"
#include "../table.h"

rook::rook(side s, player_type p) : piece(p) {
	pair<char, char> pos;
	if (p == white) {
		if (s == k) {
			set_name("♖");
			pos = pair<char, char>('H', 1);
		} else  {
			set_name("♖");
			pos = pair<char, char>('A', 1);
		}
	} else {
		if (s == k) {
			set_name("♜");
			pos = pair<char, char>('H', 8);
		} else {
			set_name("♜");
			pos = pair<char, char>('A', 8);
		}
	}
	piece::set_position(pos);
	table::get_instance().set_piece(this, pos);
}

vector<move> rook::get_possible_moves() {
	table &t = table::get_instance();

	vector<move> moves = {};

	pair<char, char> pos = piece::get_position();
	pair<char, char> next_pos;

	int i;

	// up
	for (i = 1; i <= 8 - pos.second; ++i) {
		next_pos = pair<char, char>(pos.first, pos.second + i);
		if (t.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down
	for (i = 1; i <= pos.second - 1; ++i) {
		next_pos = pair<char, char>(pos.first, pos.second - i);
		if (t.is_valid_move(move(pos, next_pos)))
            moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// left
	for (i = 1; i <= pos.first - 'A'; ++i) {
		next_pos = pair<char, char>(pos.first - i, pos.second);
		if (t.is_valid_move(move(pos, next_pos)))
            moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// right
	for (i = 1; i <= 'H' - pos.first; ++i) {
		next_pos = pair<char, char>(pos.first + i, pos.second);
		if (t.is_valid_move(move(pos, next_pos)))
            moves.emplace_back(pos, next_pos);
		else
			break;
	}

    return moves;
}
