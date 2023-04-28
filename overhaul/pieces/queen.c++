//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "queen.h"

queen::queen(player_type type) : piece(type) {
	switch (type) {
		case WHITE:
			set_default_position({'E', '1'});
			break;
		case BLACK:
			set_default_position({'E', '8'});
			break;
	}
}

string queen::to_string(style style) {
	switch (style) {
		case BOT:
			return "Q";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2655";
				case BLACK: return "\u265B";
			}
			break;
		default: break;
	}
}

vector<move> queen::get_possible_moves() {
	vector<move> moves;
	board &board = board::get_instance();

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

	// up left
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first - i, pos.second + i);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// up right
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first + i, pos.second + i);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down left
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first - i, pos.second - i);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	// down right
	for (int i = 1; i < 8; i++) {
		next_pos = position (pos.first + i, pos.second - i);
		if (board.is_valid_move(move(pos, next_pos)))
			moves.emplace_back(pos, next_pos);
		else
			break;
	}

	return moves;
}

bool queen::see_king() {
	board &board = board::get_instance();

	position pos = board[this];
	position next_pos;

	// up
	for (int i = 1; i <= 8 - pos.second; ++i) {
        next_pos = position(pos.first, pos.second + i);

		if (get_to_king(move(pos, next_pos))) return true;
    }

	// down
	for (int i = 1; i <= pos.second - 1; ++i) {
        next_pos = position(pos.first, pos.second - i);

        if (get_to_king(move(pos, next_pos))) return true;
    }

	// left
	for (int i = 1; i <= pos.first - 'A'; ++i) {
        next_pos = position(pos.first - i, pos.second);

        if (get_to_king(move(pos, next_pos))) return true;
    }

	// right
	for (int i = 1; i <= 'H' - pos.first; ++i) {
        next_pos = position(pos.first + i, pos.second);

        if (get_to_king(move(pos, next_pos))) return true;
    }

	// diagonals
	for (int i = 1; i < 8; i++) {
        // up left
        next_pos = position(pos.first - i, pos.second + i);
        if (get_to_king(move(pos, next_pos))) return true;

        // up right
        next_pos = position(pos.first + i, pos.second + i);
        if (get_to_king(move(pos, next_pos))) return true;

        // down left
        next_pos = position(pos.first - i, pos.second - i);
        if (get_to_king(move(pos, next_pos))) return true;

        // down right
        next_pos = position (pos.first + i, pos.second - i);
        if (get_to_king(move(pos, next_pos))) return true;
    }
	return false;
}
