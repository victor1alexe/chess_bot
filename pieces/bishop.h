//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_BISHOP_H
#define CRAZYHOUSE_BISHOP_H

#include "piece.h"

class bishop : public piece {
private:

public:
	bishop();
	bishop(side s, player_type p);
	~bishop() = default;
	vector<move> get_possible_moves() override;
};

#endif //CRAZYHOUSE_BISHOP_H
