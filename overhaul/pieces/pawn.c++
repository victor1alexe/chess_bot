//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "../board.h"
#include "pawn.h"

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

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
    return "";
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
			if (board.is_valid_move(move(pos, next_pos))
				&& board[next_pos] == nullptr) {
				moves.emplace_back(pos, next_pos);
			}

			// double-up
			if (pos.second == '2') {
				next_pos = position(pos.first, pos.second + 2);
				if (board.is_valid_move(move(pos, next_pos))
					&& board[position(pos.first, pos.second + 1)] == nullptr
                    && board[next_pos] == nullptr)
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
			move last_move = board.get_last_move();
			if (last_move == move::START) break;
			if (last_move.get_from().second == '7' &&
                last_move.get_to().second == '5' &&
                last_move.get_to().second == pos.second &&
                instanceof<pawn>(board[last_move.get_to()])) {
				if (last_move.get_to().first == pos.first + 1) {
                    move m = move(pos, position(pos.first + 1, '6'), EN_PASSANT);
                    if (!board.would_be_check(m))
                        moves.emplace_back(m);
                }
				if (last_move.get_to().first == pos.first - 1) {
                    move m = move(pos, position(pos.first - 1, '6'), EN_PASSANT);
                    if (!board.would_be_check(m))
                        moves.emplace_back(m);
                }
            }
			break;
		}
		case BLACK: {
			// down
			next_pos = position(pos.first, pos.second - 1);
			if (board.is_valid_move(move(pos, next_pos))
				&& board[next_pos] == nullptr) {
				moves.emplace_back(pos, next_pos);
			}

			// double-down
			if (pos.second == '7') {
				next_pos = position(pos.first, pos.second - 2);
				if (board.is_valid_move(move(pos, next_pos))
					&& board[position(pos.first, pos.second - 1)] == nullptr
                    && board[next_pos] == nullptr)
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
			move last_move = board.get_last_move();
			if (last_move.get_from().second == '2' &&
                last_move.get_to().second == '4' &&
                last_move.get_to().second == pos.second &&
                instanceof<pawn>(board[last_move.get_to()])){
                if (last_move.get_to().first == pos.first + 1) {
                    move m = move(pos, position(pos.first + 1, '3'), EN_PASSANT);
                    if (!board.would_be_check(m))
                        moves.emplace_back(m);
                }
                if (last_move.get_to().first == pos.first - 1) {
                    move m = move(pos, position(pos.first - 1, '3'), EN_PASSANT);
                    if (!board.would_be_check(m))
                        moves.emplace_back(m);
                }
            }
			break;
		}
	}

    return moves;
}

bool pawn::see_king() {
	board& board = board::get_instance();

	position pos = board[this];
	position next_pos;

	switch (get_type()) {
        case WHITE: {
            // turn-right
            next_pos = position(pos.first + 1, pos.second + 1);

			//	If it can see a piece
			if (board.is_in_bounds(next_pos)
				&& board[next_pos] != nullptr
				&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
				if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
					return true;
			}

            // turn-left
            next_pos = position(pos.first - 1, pos.second + 1);

			//	If it can see a piece
			if (board.is_in_bounds(next_pos)
				&& board[next_pos] != nullptr
				&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
				if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
					return true;
			}

            break;
        }
        case BLACK: {
            // turn-right
            next_pos = position(pos.first + 1, pos.second - 1);

			//	If it can see a piece
			if (board.is_in_bounds(next_pos)
				&& board[next_pos] != nullptr
				&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
				if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
					return true;
			}

            // turn-left
            next_pos = position(pos.first - 1, pos.second - 1);

			//	If it can see a piece
			if (board.is_in_bounds(next_pos)
				&& board[next_pos] != nullptr
				&& board[next_pos]->get_type() != get_type()) {
//			If piece found is king
				if (board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
					return true;
			}

            break;
        }
    }
	return false;
}