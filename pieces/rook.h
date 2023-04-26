//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_ROOK_H
#define CRAZYHOUSE_ROOK_H

#include "piece.h"
#include <vector>
#include "../move.h"

class rook : public piece {
private:

public:
	rook() = default;
	rook(side s, player_type p);
	~rook() = default;
	vector<move> get_possible_moves();
};


#endif //CRAZYHOUSE_ROOK_H
