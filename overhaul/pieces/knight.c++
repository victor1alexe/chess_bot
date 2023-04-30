//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "knight.h"
#include <functional>

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

knight::knight(player_type type) : piece(type) {}

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
    return "";
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

bool knight::see_king() {
	board& board = board::get_instance();
	position pos = board[this];
	position next_pos;

	// 2 up 1 right
	next_pos = position(pos.first + 1, pos.second + 2);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
			if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
				return true;
	}

	// 2 up 1 left
	next_pos = position(pos.first - 1, pos.second + 2);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}

	// 2 down 1 right
	next_pos = position(pos.first + 1, pos.second - 2);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}
	// 2 down 1 left
	next_pos = position(pos.first - 1, pos.second - 2);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}

	// 2 right 1 up
	next_pos = position(pos.first + 2, pos.second + 1);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}

	// 2 right 1 down
	next_pos = position(pos.first + 2, pos.second - 1);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}

	// 2 left 1 up
	next_pos = position(pos.first - 2, pos.second + 1);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}

	// 2 left 1 down
	next_pos = position(pos.first - 2, pos.second - 1);
//	If it can see a piece
	if (board.is_in_bounds(next_pos)
		&& board[next_pos] != nullptr
		&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
		if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
			return true;
	}

	return false;
}
