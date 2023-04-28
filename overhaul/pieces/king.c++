//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "king.h"

king::king(player_type type) : piece(type), short_castle(true), long_castle(true) {
	switch (type) {
		case WHITE:
			set_default_position({'D', '1'});
			break;
		case BLACK:
			set_default_position({'D', '8'});
			break;
	}
}

string king::to_string(style style) {
	switch (style) {
		case BOT:
			return "K";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2654";
				case BLACK: return "\u265A";
			}
			break;
		default: break;
	}
}

vector<move> king::get_possible_moves() {
	vector<move> moves;
	board &board = board::get_instance();

	position pos = board[this];
	position next_pos;

	// up
	next_pos = position(pos.first, pos.second + 1);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// down
	next_pos = position(pos.first, pos.second - 1);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// left
	next_pos = position(pos.first - 1, pos.second);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// right
	next_pos = position(pos.first + 1, pos.second);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// up left
	next_pos = position(pos.first - 1, pos.second + 1);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// up right
	next_pos = position(pos.first + 1, pos.second + 1);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// down left
	next_pos = position(pos.first - 1, pos.second - 1);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	// down right
	next_pos = position(pos.first + 1, pos.second - 1);
	if(board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(pos, next_pos);

	return moves;
}

bool king::see_king() {
	return true;
}

bool king::can_short_castle() const {
	return short_castle;
}

bool king::can_long_castle() const {
	return long_castle;
}

void king::set_short_castle(bool sc) {
	short_castle = sc;
}

void king::set_long_castle(bool lc) {
	long_castle = lc;
}