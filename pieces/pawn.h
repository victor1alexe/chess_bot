//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_PAWN_H
#define CRAZYHOUSE_PAWN_H

#include "piece.h"
#include <vector>
#include "../move.h"

class pawn : public piece {
private:

public:
	pawn(string name, player_type p);
	~pawn() = default;
	vector<move> get_possible_moves();
};


#endif //CRAZYHOUSE_PAWN_H
