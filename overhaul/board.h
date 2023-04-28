//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_BOARD_H
#define CRAZYHOUSE_BOARD_H

#include <map>
#include "player.h"
#include <stack>

using std::map, std::stack;

struct backup {
	map<position, piece*> pieces_cp;
	map<piece*, position> positions_cp;
	stack <move> moves_cp;
	player white_cp;
	player black_cp;
	backup();
	~backup() = default;
};

class board {
private:
	static board* instance;
	map<position, piece*> pieces;
	map<piece*, position> positions;
	stack<move> moves;
	player white;
	player black;
	backup* _backup;
	board();
public:
	board(board& other) = delete;
	static board& get_instance();
	position get_position(piece* piece);
	piece* get_piece(position position);
	map<position, piece*> get_pieces();
	map<piece*, position> get_positions();
	stack<move> get_moves();
	void display() const;
	void reset();

	position& operator[](piece* piece);
	piece* operator[](position position);

	bool is_valid_move(move m);
	static bool is_in_bounds(position position);

	const move& get_last_move() const;

	const player& get_white() const;
	const player& get_black() const;

	void make_move(move m);
	bool would_be_check(move m);

	void make_backup();
	void restore();
};



#endif //CRAZYHOUSE_BOARD_H
