//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_PLAYER_H
#define CRAZYHOUSE_PLAYER_H

#include <vector>
#include "piece.h"

using std::vector;

class player {
private:
	player_type type;
	vector<piece*> pieces_on_board;
	vector<piece*> pieces_in_hand;
public:
	player() = default;
	player(player_type type);
	player_type get_type();
	void add_piece(piece* p);
	void init_pieces();
	auto begin() -> decltype(pieces_on_board.begin());
	auto end() -> decltype(pieces_on_board.end());
	piece* operator[](int index);
};

#endif //CRAZYHOUSE_PLAYER_H
