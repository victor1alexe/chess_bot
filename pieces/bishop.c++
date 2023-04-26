//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include "bishop.h"
#include "../table.h"

bishop::bishop(side s, player_type p) : piece(p) {
	pair<char, char> pos;
	if (p == white) {
		if (s == k) {
			set_name("♗");
			pos = pair<char, char>('F', 1);
		} else  {
			set_name("♗");
			pos = pair<char, char>('C', 1);
		}
	} else {
		if (s == k) {
			set_name("♝");
			pos = pair<char, char>('F', 8);
		} else {
			set_name("♝");
			pos = pair<char, char>('C', 8);
		}
	}
	piece::set_position(pos);
	table::get_instance().set_piece(this, pos);
}

vector<move> bishop::get_possible_moves() {
	vector<move> moves = {};
	table& t = table::get_instance();
	pair<char, char> pos = get_position();
	pair<char, char> next_pos;

	// up left
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first - i, pos.second + i);
		if (table::is_valid_move(move(pos, next_pos)))
			moves.emplace_back(move(pos, next_pos));
		else
			break;
	}

	// up right
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first + i, pos.second + i);
		if (table::is_valid_move(move(pos, next_pos)))
			moves.emplace_back(move(pos, next_pos));
		else
			break;
	}

	// down left
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first - i, pos.second - i);
		if (table::is_valid_move(move(pos, next_pos)))
			moves.emplace_back(move(pos, next_pos));
		else
			break;
	}

	// down right
	for (int i = 1; i < 8; i++) {
		next_pos = pair<char, char>(pos.first + i, pos.second - i);
		if (table::is_valid_move(move(pos, next_pos)))
			moves.emplace_back(move(pos, next_pos));
		else
			break;
	}

	return moves;
}