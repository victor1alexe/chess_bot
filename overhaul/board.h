//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_BOARD_H
#define CRAZYHOUSE_BOARD_H

#include <map>
#include "player.h"

using std::map;

class board {
private:
	static board* instance;
	map<position, piece*> pieces;
	map<piece*, position> positions;
	player white;
	player black;
	board();
public:
	board(board& other) = delete;
	static board& get_instance();
	position get_position(piece* piece);
	piece* get_piece(position position);
	void display() const;
	void reset();

	position& operator[](piece* piece);
	piece* operator[](position position);

	bool is_valid_move(move m);
	bool is_in_bounds(position position);

	const player& get_white() const;
	const player& get_black() const;

	void make_move(move m);
};


#endif //CRAZYHOUSE_BOARD_H
