//
// Created by Eduard Andrei Radu on 21.04.2023.
//
#include "knight.h"
#include "../table.h"

using std::vector;

knight::knight(side s, player_type p) : piece(p) {
	pair<char, char> pos;
	if (p == white) {
		if (s == k) {
			set_name("♘");
			pos = pair<char, char>('G', 1);
		} else {
			set_name("♘");
			pos = pair<char, char>('B', 1);
		}
	} else {
		if (s == k) {
			set_name("♞");
			pos = pair<char, char>('G', 8);
		} else {
			set_name("♞");
			pos = pair<char, char>('B', 8);
		}
	}
	piece::set_position(pos);
	table::get_instance().set_piece(this, pos);
}


vector<move> knight::get_possible_moves() {
	vector<move> moves = {};
	table &t = table::get_instance();
	pair<char, char> pos = piece::get_position();
	pair<char, char> next_pos;

	// 2 up 1 right
	next_pos = pair<char, char>(pos.first + 1, pos.second + 2);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 up 1 left
	next_pos = pair<char, char>(pos.first - 1, pos.second + 2);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 down 1 right
	next_pos = pair<char, char>(pos.first + 1, pos.second - 2);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 down 1 left
	next_pos = pair<char, char>(pos.first - 1, pos.second - 2);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 right 1 up
	next_pos = pair<char, char>(pos.first + 2, pos.second + 1);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 right 1 down
	next_pos = pair<char, char>(pos.first + 2, pos.second - 1);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 left 1 up
	next_pos = pair<char, char>(pos.first - 2, pos.second + 1);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 left 1 down
	next_pos = pair<char, char>(pos.first - 2, pos.second - 1);
	if (table::is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	return moves;
}
