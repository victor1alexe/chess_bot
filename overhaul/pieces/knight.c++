//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "knight.h"

knight::knight(player_type type, side side) : piece(type) {
	switch (type) {
		case WHITE:
			switch (side) {
				case QUEEN:
					set_default_position({'B', '1'});
					break;
				case KING:
					set_default_position({'G', '1'});
					break;
			}
			break;
		case BLACK:
			switch (side) {
				case QUEEN:
					set_default_position({'B', '8'});
					break;
				case KING:
					set_default_position({'G', '8'});
					break;
			}
			break;
	}
}

string knight::to_string(style style) {
	switch (style) {
		case BOT:
			return "N";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2658";
				case BLACK: return "\u265E";
			}
			break;
		default: break;
	}
}

vector<move> knight::get_possible_moves() {
	vector<move> moves;
	board& board = board::get_instance();

	position pos = board[this];
	position next_pos;

	// 2 up 1 right
	next_pos = position(pos.first + 1, pos.second + 2);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 up 1 left
	next_pos = position(pos.first - 1, pos.second + 2);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 down 1 right
	next_pos = position(pos.first + 1, pos.second - 2);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 down 1 left
	next_pos = position(pos.first - 1, pos.second - 2);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 right 1 up
	next_pos = position(pos.first + 2, pos.second + 1);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 right 1 down
	next_pos = position(pos.first + 2, pos.second - 1);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 left 1 up
	next_pos = position(pos.first - 2, pos.second + 1);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	// 2 left 1 down
	next_pos = position(pos.first - 2, pos.second - 1);
	if (board.is_valid_move(move(pos, next_pos)))
		moves.emplace_back(move(pos, next_pos));

	return moves;
}
