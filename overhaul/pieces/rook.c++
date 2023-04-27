//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "rook.h"

rook::rook(player_type type, side side) : piece(type) {
	switch (type) {
		case WHITE:
			switch (side) {
				case QUEEN:
					set_default_position({'A', '1'});
					break;
				case KING:
					set_default_position({'H', '1'});
					break;
			}
			break;
		case BLACK:
			switch (side) {
				case QUEEN:
					set_default_position({'A', '8'});
					break;
				case KING:
					set_default_position({'H', '8'});
					break;
			}
			break;
	}
}

string rook::to_string(style style) {
	switch (style) {
		case BOT:
			return "R";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2656";
				case BLACK: return "\u265C";
			}
			break;
		default: break;
	}
}

vector<move> rook::get_possible_moves() {
	vector<move> moves;
	board& board = board::get_instance();

	position pos = board[this];
	position next_pos;

	// up
	for (int i = 1; i <= 8 - pos.second; ++i) {
		next_pos = position(pos.first, pos.second + i);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down
	for (int i = 1; i <= pos.second - 1; ++i) {
		next_pos = position(pos.first, pos.second - i);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// left
	for (int i = 1; i <= pos.first - 'A'; ++i) {
		next_pos = position(pos.first - i, pos.second);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// right
	for (int i = 1; i <= 'H' - pos.first; ++i) {
		next_pos = position(pos.first + i, pos.second);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	return moves;
}

bool rook::see_king() {
	board &board = board::get_instance();
	position pos = board[this];
	position next_pos;

	for (int i = 1; i <= 8 - pos.second; ++i) {
        next_pos = position(pos.first, pos.second + i);
		if (would_be_in_check(move(pos, next_pos))) return true;

		next_pos = position(pos.first, pos.second - i);
		if (would_be_in_check(move(pos, next_pos))) return true;

		next_pos = position(pos.first - i, pos.second);
		if (would_be_in_check(move(pos, next_pos))) return true;

		next_pos = position(pos.first + i, pos.second);
		if (would_be_in_check(move(pos, next_pos))) return true;
    }

	return false;
}