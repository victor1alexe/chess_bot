//
// Created by Eduard Andrei Radu on 22.04.2023.
//
#include "pieces/extra.h"
#include "pieces/piece.h"

#ifndef CRAZYHOUSE_PLAYER_H
#define CRAZYHOUSE_PLAYER_H

class player {
private:
	player_type type;
	vector<piece*> pieces;
public:
	explicit player(player_type type);
	~player();
	vector<move> get_possible_moves();
	move make_move();
};


#endif //CRAZYHOUSE_PLAYER_H
