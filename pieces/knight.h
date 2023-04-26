//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_KNIGHT_H
#define CRAZYHOUSE_KNIGHT_H

#include "piece.h"
#include <vector>
#include "../move.h"

class knight : public piece {
private:

public:
	knight(side s, player_type p);
	~knight() = default;
	vector<move> get_possible_moves();
};

#endif //CRAZYHOUSE_KNIGHT_H
