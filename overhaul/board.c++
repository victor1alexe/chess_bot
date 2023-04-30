//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include <iostream>
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "board.h"

using std::cout, std::endl;
using position = pair<char, char>;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

board *board::instance = new board();

board& board::get_instance() {
	return *instance;
}

player_type board::get_current_player() const {
    return current_player;
}

void board::set_current_player(player_type p_t) {
    current_player = p_t;
}

board::board() : white(WHITE), black(BLACK), _backup(nullptr) {
	reset();
    reset_moves_since_last_capture();
}

void board::set_powered_on(bool powered_on) {
    this->powered_on = powered_on;
}

bool board::is_powered_on() const {
    return powered_on;
}

position board::get_position(piece *piece) {
	return positions[piece];
}

piece *board::get_piece(position position) {
	if (pieces.find(position) == pieces.end()) {
		return nullptr;
	}
	return pieces[position];
}

void board::display() const {
	cout << "┏━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┓" << endl;
	for (char i = '8'; i >= '1'; i--) {
        cout << "┃ " << i << " ";
		for (char j = 'A'; j <= 'H'; j++) {
			position pos = position(j, i);
			if (pieces.find(pos) == pieces.end()) {
				cout << "┃   ";
			} else {
				cout << "┃ " << pieces.at(pos)->to_string(DEBUG) << ' ';
			}
		}
		cout << "┃" << endl;
        cout << "┣━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━┫" << endl;
	}
    cout << "┃ O ┃ A ┃ B ┃ C ┃ D ┃ E ┃ F ┃ G ┃ H ┃" << endl;
	cout << "┗━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┛" << endl;
}

position& board::operator[](piece* piece) {
	if (positions.find(piece) == positions.end()) {
		return OUT;
	}
	return positions[piece];
}

piece* board::operator[](position position) {
	if (pieces.find(position) == pieces.end()) {
		return nullptr;
	}
	return pieces[position];
}

void board::reset() {
	pieces = map<position, piece*>();
	positions = map<piece*, position>();

    white = player(WHITE);
    black = player(BLACK);

	white.init_pieces();
	black.init_pieces();

    set_powered_on(false);

	for (auto& piece : white) {
		pieces[piece->get_default_position()] = piece;
		positions[piece] = piece->get_default_position();
	}

	for (auto& piece : black) {
		pieces[piece->get_default_position()] = piece;
		positions[piece] = piece->get_default_position();
	}
}

bool board::is_in_bounds(position position) {
	return position.first >= 'A' && position.first <= 'H' && position.second >= '1' && position.second <= '8';
}

player& board::get_white() {
	return white;
}

player& board::get_black() {
	return black;
}

const move& board::get_last_move() const {
	if (moves.empty()) return move::START;
    return moves.top();
}

bool board::would_be_check(move m) {
	board& b = get_instance();

	b.make_backup();
	b.make_move(m);
    piece *k;
    if (m.get_special() == DROP_WHITE)
        k = white.get_king();
    else if (m.get_special() == DROP_BLACK)
        k = black.get_king();
    else
        k = (get_piece(m.get_to())->get_type() == WHITE) ? white.get_king() : black.get_king();

	position king_pos = positions[k];

	bool would_be_in_check = false;
	position p;
	vector<piece*> pieces = {};

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first + i, king_pos.second + i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first - i, king_pos.second + i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first + i, king_pos.second - i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first - i, king_pos.second - i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first + i, king_pos.second);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first - i, king_pos.second);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first, king_pos.second + i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

	for (int i = 1; i < 8; i++) {
		p = position(king_pos.first, king_pos.second - i);
		if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
			pieces.push_back(b[p]);
			break;
		}
	}

    // Check for knights
    p = position(king_pos.first + 1, king_pos.second + 2);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first + 1, king_pos.second - 2);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first - 1, king_pos.second + 2);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first - 1, king_pos.second - 2);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first + 2, king_pos.second + 1);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first + 2, king_pos.second - 1);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first - 2, king_pos.second + 1);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

    p = position(king_pos.first - 2, king_pos.second - 1);
    if (b.is_in_bounds(p) && (b[p] != nullptr) && (b[p]->get_type() != k->get_type())) {
        pieces.push_back(b[p]);
    }

	std::for_each(pieces.begin(), pieces.end(), [&](piece* p) {
		if (p->see_king()) {
			would_be_in_check = true;
		}
	});

	b.restore();
	return would_be_in_check;
}

bool board::is_valid_move(move m) {
//	Get start and end positions
	const position to = m.get_to();
	const position from = m.get_from();

//	Get current player at start position
	player_type p = get_piece(from)->get_type();

//	If the end position is out of bounds, return false
	bool in_bounds = is_in_bounds(to);
	if (!in_bounds) return false;

// 	If the move puts the king in check, return false
	bool would_be_in_check = would_be_check(m);
	if (would_be_in_check) return false;

//	If the end position is empty, return true
	bool is_empty = get_piece(to) == nullptr;
	if(is_empty) return true;

//	If the end position is occupied by a piece of the same color, return false
	bool is_available = get_piece(to)->get_type() != p;
	if (!is_available) return false;

	return true;
}

bool board::is_castle_possible(player_type p_t, side s) {
	player p = (p_t == WHITE) ? white : black;
    if (p.is_in_check()) return false;
	switch (p_t) {
		case WHITE:
			switch (s) {
				case QUEEN:
					if (p.can_long_castle()) {
						piece* queen = (*this)[{'D', '1'}];
						piece* bishop = (*this)[{'C', '1'}];
						piece* knight = (*this)[{'B', '1'}];
						if (queen != nullptr || bishop != nullptr || knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E1D1"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E1C1"))) {
							restore();
							return false;
						}
						return true;
					}
					break;
				case KING:
					if (p.can_short_castle()) {
						piece* bishop = (*this)[{'F', '1'}];
						piece* knight = (*this)[{'G', '1'}];
						if (bishop != nullptr || knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E1F1"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E1G1"))) {
							restore();
							return false;
						}

						return true;
					}
					break;
				default:
					break;
			}
			break;
		case BLACK:
			switch (s) {
				case QUEEN:
					if (p.can_long_castle()) {
						piece* queen = (*this)[{'D', '8'}];
						piece* bishop = (*this)[{'C', '8'}];
						piece* knight = (*this)[{'B', '8'}];
						if (queen != nullptr || bishop != nullptr || knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E8D8"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E8C8"))) {
							restore();
							return false;
						}
						return true;
					}
					break;
				case KING:
					if (p.can_short_castle()) {
						piece* bishop = (*this)[{'F', '8'}];
						piece* knight = (*this)[{'G', '8'}];
						if (bishop != nullptr || knight != nullptr) return false;
						make_backup();
						if (would_be_check(move("E8F8"))) {
							restore();
							return false;
						}
						restore();

						if (would_be_check(move("E8G8"))) {
							restore();
							return false;
						}

						return true;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return false;
}

void board::make_move(move m) {
    const position to = m.get_to();
	const position from = m.get_from();

    if (m.get_special() == DROP_WHITE) {
        piece* p;
        switch (m.get_from().first) {
            case 'P':
                p = new pawn(WHITE, 'A');
                get_white().place_piece(p);
                break;
            case 'R':
                p = new rook(WHITE, QUEEN);
                get_white().place_piece(p);

                break;
            case 'N':
                p = new knight(WHITE, QUEEN);
                get_white().place_piece(p);
                break;
            case 'B':
                p = new bishop(WHITE, QUEEN);
                get_white().place_piece(p);
                break;
            case 'Q':
                p = new queen(WHITE);
                get_white().place_piece(p);
                break;
        }
        pieces[m.get_to()] = p;
        positions[p] = m.get_to();
        return;
    }
    if (m.get_special() == DROP_BLACK) {
        piece* p;
        switch (m.get_from().first) {
            case 'P':
                p = new pawn(BLACK, 'A');
                get_black().place_piece(p);
                break;
            case 'R':
                p = new rook(BLACK, QUEEN);
                get_black().place_piece(p);
                break;
            case 'N':
                p = new knight(BLACK, QUEEN);
                get_black().place_piece(p);
                break;
            case 'B':
                p = new bishop(BLACK, QUEEN);
                get_black().place_piece(p);
                break;
            case 'Q':
                p = new queen(BLACK);
                get_black().place_piece(p);
                break;
        }
        pieces[m.get_to()] = p;
        positions[p] = m.get_to();
        return;
    }

	piece* attacker = get_piece(from);;
	piece* captured = nullptr;

	player& me = attacker->get_type() == WHITE ? white : black;
	player& him = attacker->get_type() == WHITE ? black : white;


    if (from.first == 'E' && (from.second == '1' || from.second == '8')) {
        me.set_short_castle(false);
        me.set_long_castle(false);
    }

    if (from.first == 'H' && (from.second == '1' || from.second == '8')) {
        me.set_short_castle(false);
    }

    if (from.first == 'A' && (from.second == '1' || from.second == '8')) {
        me.set_long_castle(false);
    }


	switch (m.get_special()) {
		case SHORT_CASTLE:
            if (attacker->get_type() == WHITE) {
                make_move(move("H1F1"));
                make_move(move("E1G1"));
                me.set_short_castle(false);
                me.set_long_castle(false);
            } else {
                make_move(move("H8F8"));
                make_move(move("E8G8"));
                me.set_short_castle(false);
                me.set_long_castle(false);
            }
			break;
		case LONG_CASTLE:
            if (attacker->get_type() == WHITE) {
                make_move(move("A1D1"));
                make_move(move("E1C1"));
                me.set_short_castle(false);
                me.set_long_castle(false);
            } else {
                make_move(move("A8D8"));
                make_move(move("E8C8"));
                me.set_short_castle(false);
                me.set_long_castle(false);
            }
			break;
		case EN_PASSANT:
			if (me.get_type() == WHITE)
				captured = get_piece(position(to.first, to.second - 1));
			else
				captured = get_piece(position(to.first, to.second + 1));

			me.capture_piece(captured);
			him.remove_piece(captured);

			pieces.erase((*this)[captured]);
			positions.erase(captured);

			pieces.erase(from);
			positions.erase(attacker);

			pieces[to] = attacker;
			positions[attacker] = to;

            // delete captured;
            reset_moves_since_last_capture();
			break;

		case PROMOTION:
			break;
		default:
			captured = get_piece(to);

			if (captured != nullptr) {
                reset_moves_since_last_capture();
				me.capture_piece(captured);
				him.remove_piece(captured);
				pieces.erase(to);
				positions.erase(captured);
                // delete captured;
			} else {
                if (instanceof<pawn>(attacker))
                    reset_moves_since_last_capture();
                else
                    increment_moves_since_last_capture();
            }
			pieces.erase(from);
			positions.erase(attacker);

			pieces[to] = attacker;
			positions[attacker] = to;

            // check if white pawn is on last line to promote
            if (attacker->get_type() == WHITE && to.second == '8' && instanceof<pawn>(attacker)) {
                //cout << "Promotion WHITE" << endl;
                me.remove_piece(attacker);
                pieces.erase(to);
                positions.erase(attacker);
                attacker = new queen(WHITE);
                attacker->set_promotion(true);
                me.add_piece(attacker);
                pieces[to] = attacker;
                positions[attacker] = to;
            } else if (attacker->get_type() == BLACK && to.second == '1' && instanceof<pawn>(attacker)) {
                //cout << "Promotion BLACK" << endl;
                me.remove_piece(attacker);
                pieces.erase(to);
                positions.erase(attacker);
                attacker = new queen(BLACK);
                attacker->set_promotion(true);
                me.add_piece(attacker);
                pieces[to] = attacker;
                positions[attacker] = to;
            }
			break;
	}

	him.set_in_check(attacker->see_king());
	me.set_in_check(false);
	moves.push(m);
}

map<piece*, position> board::get_positions() {
	return positions;
}

map<position, piece*> board::get_pieces() {
	return pieces;
}

stack<move> board::get_moves() {
	return moves;
}

backup::backup() {
	pieces_cp = board::get_instance().get_pieces();
	positions_cp = board::get_instance().get_positions();
	moves_cp = board::get_instance().get_moves();
	white_cp = board::get_instance().get_white();
	black_cp = board::get_instance().get_black();
}

void board::make_backup() {
	_backup = new backup();
}

void board::restore() {
	pieces = _backup->pieces_cp;
	positions = _backup->positions_cp;
	moves = _backup->moves_cp;
	white = _backup->white_cp;
	black = _backup->black_cp;
}

int board::get_moves_since_last_capture() const {
    return moves_since_last_capture;
}

void board::increment_moves_since_last_capture() {
    moves_since_last_capture++;
}

void board::reset_moves_since_last_capture() {
    moves_since_last_capture = 0;
}