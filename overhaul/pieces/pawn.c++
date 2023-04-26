//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "pawn.h"

pawn::pawn(player_type type, char file) : piece(type), file(file) {
	switch (type) {
		case WHITE:
			set_default_position({file, '2'});
			break;
		case BLACK:
			set_default_position({file, '7'});
			break;
	}
}

string pawn::to_string(style style) {
	switch (style) {
		case BOT:
			return std::string(1, file) + (get_type() == WHITE ? std::string(1, '2') : std::string(1, '7'));
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2659";
				case BLACK: return "\u265F";
			}
			break;
		default: break;
	}
}

vector<move> pawn::get_possible_moves() {
    vector<move> moves;
	board& board = board::get_instance();

	position pos = board[this];
	position next_pos;

	switch (get_type()) {
		case WHITE: {
			// up
			next_pos = position(pos.first, pos.second + 1);
			if (board.is_valid_move(move(pos, next_pos))) {
				moves.emplace_back(pos, next_pos);
			}

			// double-up
			if (pos.second == '2') {
				next_pos = position(pos.first, pos.second + 2);
				if (board.is_valid_move(move(pos, next_pos)))
					moves.emplace_back(pos, next_pos);
			}

			// turn-right
			next_pos = position(pos.first + 1, pos.second + 1);
			if (board.is_valid_move(move(pos, next_pos))
				&& board[next_pos] != nullptr
				&& board[next_pos]->get_type() == BLACK) {

				moves.emplace_back(pos, next_pos);
			}

			// turn-left
			next_pos = position(pos.first - 1, pos.second + 1);
			if (board.is_valid_move(move(pos, next_pos))
				&& board[next_pos] != nullptr
				&& board[next_pos]->get_type() == BLACK) {

				moves.emplace_back(pos, next_pos);
			}

			// en-passant
			break;
		}
		case BLACK: {
			// down
			next_pos = position(pos.first, pos.second - 1);
			if (board.is_valid_move(move(pos, next_pos))) {
				moves.emplace_back(pos, next_pos);
			}

			// double-down
			if (pos.second == '7') {
				next_pos = position(pos.first, pos.second - 2);
				if (board.is_valid_move(move(pos, next_pos)))
					moves.emplace_back(pos, next_pos);
			}

			// turn-right
			next_pos = position(pos.first + 1, pos.second - 1);
			if (board.is_valid_move(move(pos, next_pos)) &&
				board[next_pos] != nullptr &&
				board[next_pos]->get_type() == WHITE) {

				moves.emplace_back(pos, next_pos);
			}

			// turn-left
			next_pos = position(pos.first - 1, pos.second - 1);
			if (board.is_valid_move(move(pos, next_pos)) &&
				board[next_pos] != nullptr &&
				board[next_pos]->get_type() == WHITE) {

				moves.emplace_back(pos, next_pos);
			}

			// en-passant
			break;
		}
	}

    return moves;
}