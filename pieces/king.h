//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_KING_H
#define CRAZYHOUSE_KING_H


#include "piece.h"
#include <vector>
#include "../move.h"

class king : public piece {
private:

public:
	king() = default;
	king(player_type p);
	~king() = default;
	vector<move> get_possible_moves();
};
#endif //CRAZYHOUSE_KING_H
