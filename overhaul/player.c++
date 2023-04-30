#include "player.h"
#include "board.h"
#include "piece.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/rook.h"
#include "pieces/bishop.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include <iostream>

using std::cout, std::endl;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

player::player(player_type type) : type(type), in_check(false), long_castle(true), short_castle(true) {
	pieces_on_board = {};
	queens_in_hand = 0;
    rooks_in_hand = 0;
    knights_in_hand = 0;
    bishops_in_hand = 0;
    pawns_in_hand = 0;
}

player_type player::get_type() {
	return type;
}

void player::add_piece(piece *p) {
	pieces_on_board.push_back(p);
}

void player::set_short_castle(bool short_castle) {
    player::short_castle = short_castle;
}

void player::set_long_castle(bool long_castle) {
    player::long_castle = long_castle;
}

void player::capture_piece(piece *p) {
    if (p->is_promoted() || instanceof<pawn>(p))
        pawns_in_hand++;
    else if (instanceof<rook>(p))
        rooks_in_hand++;
    else if (instanceof<queen>(p))
        queens_in_hand++;
    else if (instanceof<knight>(p))
        knights_in_hand++;
    else if (instanceof<bishop>(p))
        bishops_in_hand++;
}

void player::remove_piece(piece *p) {
	pieces_on_board.erase(std::remove(pieces_on_board.begin(), pieces_on_board.end(), p), pieces_on_board.end());
}

void player::place_piece(piece* p) {
    if (instanceof<rook>(p))
        rooks_in_hand--;
    else if (instanceof<queen>(p))
        queens_in_hand--;
    else if (instanceof<knight>(p))
        knights_in_hand--;
    else if (instanceof<bishop>(p))
        bishops_in_hand--;
    else if (instanceof<pawn>(p))
        pawns_in_hand--;
    pieces_on_board.push_back(p);
}

bool player::can_long_castle() const {
	return long_castle;
}

bool player::can_short_castle() const {
	return short_castle;
}

void player::init_pieces() {
	my_king = new king(type);
	pieces_on_board.push_back(my_king);
	pieces_on_board.push_back(new queen(type));
	pieces_on_board.push_back(new rook(type, QUEEN));
	pieces_on_board.push_back(new rook(type, KING));
	pieces_on_board.push_back(new bishop(type, QUEEN));
	pieces_on_board.push_back(new bishop(type, KING));
	pieces_on_board.push_back(new knight(type, QUEEN));
	pieces_on_board.push_back(new knight(type, KING));
	for (char i = 'A'; i <= 'H'; i++) {
		pieces_on_board.push_back(new pawn(type, i));
	}
}


void player::set_in_check(bool in_check) {
	this->in_check = in_check;
}

bool player::is_in_check() const {
	return in_check;
}

vector<move> player::get_possible_moves() const {
	vector<move> moves = {};
	for (auto piece : pieces_on_board) {
		vector<move> piece_moves = piece->get_possible_moves();
		moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
	}
	return moves;
}

vector<move> player::get_possible_drops() {
    vector<move> moves = {};
    board& b = board::get_instance();
    vector<position> possible_places = {};
    for (char i = '1'; i <= '8'; i++) {
        for (char j = 'A'; j <= 'H'; j++) {
            if (b[position(j, i)] == nullptr) {
                possible_places.emplace_back(j, i);
            }
        }
    }
    if (pawns_in_hand != 0) {
        for (auto pos : possible_places) {
            if (pos.second != '8' && pos.second != '1') {
                move m = move({'P', '@'}, pos, get_type() == WHITE ? DROP_WHITE : DROP_BLACK);
                if (!b.would_be_check(m)) {
                    moves.emplace_back(m);
                }
            }
        }
    }
    if (rooks_in_hand != 0) {
        for (auto pos : possible_places) {
            move m = move({'R', '@'}, pos, get_type() == WHITE ? DROP_WHITE : DROP_BLACK);
            if (!b.would_be_check(m)) {
                moves.emplace_back(m);
            }
        }
    }
    if (knights_in_hand != 0) {
        for (auto pos : possible_places) {
            move m = move({'N', '@'}, pos, get_type() == WHITE ? DROP_WHITE : DROP_BLACK);
            if (!b.would_be_check(m)) {
                moves.emplace_back(m);
            }
        }
    }
    if (bishops_in_hand != 0) {
        for (auto pos : possible_places) {
            move m = move({'B', '@'}, pos, get_type() == WHITE ? DROP_WHITE : DROP_BLACK);
            if (!b.would_be_check(m)) {
                moves.emplace_back(m);
            }
        }
    }
    if (queens_in_hand != 0) {
        for (auto pos : possible_places) {
            move m = move({'Q', '@'}, pos, get_type() == WHITE ? DROP_WHITE : DROP_BLACK);
            if (!b.would_be_check(m)) {
                moves.emplace_back(m);
            }
        }
    }
    return moves;
}






auto player::begin() -> decltype(pieces_on_board.begin()) {
	return pieces_on_board.begin();
}

auto player::end() -> decltype(pieces_on_board.end()) {
	return pieces_on_board.end();
}

piece *player::operator[](int index) {
	return pieces_on_board[index];
}

piece* player::get_king() const {
	return my_king;
}