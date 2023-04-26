//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include "pawn.h"
#include "../table.h"

pawn::pawn(string name, player_type p) : piece(p) {
	pair<char, char> pos;
	string n = "   ";
	switch (p) {
	case white:
		pos = pair<char, char>(name[0], 2);
		n[0] = 'W';
		n[1] = pos.first;
		n[2] = pos.second;
		set_name("♙");
        break;

	case black:
		pos = pair<char, char>(name[0], 7);
		n[0] = 'B';
		n[1] = pos.first;
		n[2] = pos.second;
		set_name("♟");
        break;
	}

	piece::set_position(pos);
	table::get_instance().set_piece(this, pos);
}

vector<move> pawn::get_possible_moves() {
	table &t = table::get_instance();

	vector<move> moves = {};

	pair<char, char> pos = piece::get_position();
	pair<char, char> next_pos;

	switch (get_player()) {
	case white:
		// up
		next_pos = pair<char, char>(pos.first, pos.second + 1);
		if (table::is_valid_move(move(pos, next_pos))) {
			moves.emplace_back(pos, next_pos);
		}

		// double-up
		if (pos.second == 2) {
			next_pos = pair<char, char>(pos.first, pos.second + 2);
			if (table::is_valid_move(move(pos, next_pos)))
				moves.emplace_back(pos, next_pos);
		}

		// turn-right
		next_pos = pair<char, char>(pos.first + 1, pos.second + 1);
		if (table::is_valid_move(move(pos, next_pos))
			&& t.at(next_pos) != nullptr
			&& t.at(next_pos)->get_player() == black) {

			moves.emplace_back(pos, next_pos);
		}

		// turn-left
		next_pos = pair<char, char>(pos.first - 1, pos.second + 1);
		if (table::is_valid_move(move(pos, next_pos))
			&& t.at(next_pos) != nullptr
			&& t.at(next_pos)->get_player() == black) {

			moves.emplace_back(pos, next_pos);
		}

		// en-passant
		break;

	case black:
		// down
		next_pos = pair<char, char>(pos.first, pos.second - 1);
		if (table::is_valid_move(move(pos, next_pos))) {
			moves.emplace_back(pos, next_pos);
		}

		// double-down
		if (pos.second == 7) {
			next_pos = pair<char, char>(pos.first, pos.second - 2);
			if (table::is_valid_move(move(pos, next_pos)))
				moves.emplace_back(pos, next_pos);
		}

		// turn-right
		next_pos = pair<char, char>(pos.first + 1, pos.second - 1);
		if (table::is_valid_move(move(pos, next_pos)) &&
			t.at(next_pos) != nullptr &&
			t.at(next_pos)->get_player() == white) {

			moves.emplace_back(pos, next_pos);
		}

		// turn-left
		next_pos = pair<char, char>(pos.first - 1, pos.second - 1);
		if (table::is_valid_move(move(pos, next_pos)) &&
			t.at(next_pos) != nullptr &&
			t.at(next_pos)->get_player() == white) {

			moves.emplace_back(pos, next_pos);
		}

		// en-passant
		break;
	}

	return moves;
}