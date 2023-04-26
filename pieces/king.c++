//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include "king.h"
#include "../table.h"

king::king(player_type p) : piece(p) {
	pair<char, char> pos;
	if(p == white) {
		set_name("♔");
		pos = pair<char, char>('E', 1);
	}
	else{
		set_name("♚");
		pos = pair<char, char>('E', 8);
	}
	piece::set_position(pos);
	table::get_instance().set_piece(this, pos);
}

vector<move> king::get_possible_moves() {
	const table &t = table::get_instance();

	vector<move> moves = {};

	pair<char, char> pos = piece::get_position();
	pair<char, char> next_pos;

	// up
	next_pos = pair<char, char>(pos.first, pos.second + 1);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// down
	next_pos = pair<char, char>(pos.first, pos.second - 1);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// left
	next_pos = pair<char, char>(pos.first - 1, pos.second);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// right
	next_pos = pair<char, char>(pos.first + 1, pos.second);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// up left
	next_pos = pair<char, char>(pos.first - 1, pos.second + 1);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// up right
	next_pos = pair<char, char>(pos.first + 1, pos.second + 1);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// down left
	next_pos = pair<char, char>(pos.first - 1, pos.second - 1);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	// down right
	next_pos = pair<char, char>(pos.first + 1, pos.second - 1);
	if(t.is_valid_move(move(pos, next_pos)))
        moves.emplace_back(pos, next_pos);

	return moves;
}