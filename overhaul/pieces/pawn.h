//
// Created by Eduard Andrei Radu and Ionescu Gabriel Lucian Smcherul on 26.04.2023.
//

#ifndef CRAZYHOUSE_PAWN_H
#define CRAZYHOUSE_PAWN_H

#include "../piece.h"

class pawn : public piece {
private:
	char file;
public:
	pawn(player_type type, char file);
	string to_string(style style);
	vector<move> get_possible_moves();
	bool see_king();
};

#endif //CRAZYHOUSE_PAWN_H
