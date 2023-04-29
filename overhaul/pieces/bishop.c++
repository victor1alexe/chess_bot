//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "bishop.h"

bishop::bishop(player_type type, side side) : piece(type) {
	switch (type) {
		case WHITE:
			switch (side) {
				case QUEEN:
					set_default_position({'C', '1'});
					break;
				case KING:
					set_default_position({'F', '1'});
					break;
			}
			break;
		case BLACK:
			switch (side) {
				case QUEEN:
					set_default_position({'C', '8'});
					break;
				case KING:
					set_default_position({'F', '8'});
					break;
			}
			break;
	}
}

bishop::bishop(player_type type) : piece(type) {}

string bishop::to_string(style style) {
	switch (style) {
		case BOT:
			return "B";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2657";
				case BLACK: return "\u265D";
			}
			break;
		default: break;
	}
}

vector<move> bishop::get_possible_moves() {
	vector<move> moves;
	board& board = board::get_instance();

	position pos = board[this];
	position next_pos;

	// up left
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first - i, pos.second + i);
		if (board.is_valid_move(move(pos, next_pos))) {
			moves.emplace_back(move(pos, next_pos));
			if (board[next_pos] != nullptr)
				break;
		}
		else
			break;
	}

	// up right
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first + i, pos.second + i);
		if (board.is_valid_move(move(pos, next_pos))) {
			moves.emplace_back(move(pos, next_pos));
			if (board[next_pos] != nullptr)
				break;
		}
		else
			break;
	}

	// down left
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first - i, pos.second - i);
		if (board.is_valid_move(move(pos, next_pos))) {
			moves.emplace_back(move(pos, next_pos));
			if (board[next_pos] != nullptr)
				break;
		}
		else
			break;
	}

	// down right
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first + i, pos.second - i);
		if (board.is_valid_move(move(pos, next_pos))) {
			moves.emplace_back(move(pos, next_pos));
			if (board[next_pos] != nullptr)
				break;
		}
		else
			break;
	}

	return moves;
}

bool bishop::see_king() {
	board &board = board::get_instance();
	position pos = board[this];
	position next_pos;

	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first - i, pos.second + i);
		//	If it can see a piece
		if (board.is_in_bounds(next_pos)
			&& board[next_pos] != nullptr
			&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
			if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
				return true;
			else break;
		}
	}
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first + i, pos.second + i);
		//	If it can see a piece
		if (board.is_in_bounds(next_pos)
			&& board[next_pos] != nullptr
			&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
			if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
				return true;
			else break;
		}
	}
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first - i, pos.second - i);
		//	If it can see a piece
		if (board.is_in_bounds(next_pos)
			&& board[next_pos] != nullptr
			&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
			if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
				return true;
			else break;
		}
	}
	for (int i = 1; i < 8; i++) {
		next_pos = position(pos.first + i, pos.second - i);
		//	If it can see a piece
		if (board.is_in_bounds(next_pos)
			&& board[next_pos] != nullptr
			&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
			if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
				return true;
			else break;
		}
	}

	return false;
}