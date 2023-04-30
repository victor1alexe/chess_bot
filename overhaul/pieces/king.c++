#include "../board.h"
#include "king.h"

king::king(player_type type) : piece(type) {
	switch (type) {
		case WHITE:
			set_default_position({'E', '1'});
			break;
		case BLACK:
			set_default_position({'E', '8'});
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
    return "";
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

	// castling long
	if (board.is_castle_possible(get_type(), QUEEN))
        moves.emplace_back(get_type() == WHITE ? move::LONG_CASTLE_WHITE : move::LONG_CASTLE_BLACK);

    // castling short
    if (board.is_castle_possible(get_type(), KING))
        moves.emplace_back(get_type() == WHITE ? move::SHORT_CASTLE_WHITE : move::SHORT_CASTLE_BLACK);

	return moves;
}

bool king::see_king() {
	board &board = board::get_instance();
	position pos = board[this];
	position next_pos;
	// up
	next_pos = position(pos.first, pos.second + 1);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;


	// down
	next_pos = position(pos.first, pos.second - 1);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;

	// left
	next_pos = position(pos.first - 1, pos.second);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;

	// right
	next_pos = position(pos.first + 1, pos.second);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;

	// up left
	next_pos = position(pos.first - 1, pos.second + 1);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;

	// up right
	next_pos = position(pos.first + 1, pos.second + 1);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;

	// down left
	next_pos = position(pos.first - 1, pos.second - 1);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;

	// down right
	next_pos = position(pos.first + 1, pos.second - 1);
	if(board[next_pos] == ((get_type() == WHITE) ? board.get_black().get_king() : board.get_white().get_king()))
		return true;
	return false;
}