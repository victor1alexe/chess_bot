//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_QUEEN_H
#define CRAZYHOUSE_QUEEN_H

#include "piece.h"

class queen : public piece {
private:

public:
	explicit queen(player_type p);
	~queen() = default;
	vector<move> get_possible_moves();
};
#endif //CRAZYHOUSE_QUEEN_H
