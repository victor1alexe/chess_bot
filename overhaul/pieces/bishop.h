//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_BISHOP_H
#define CRAZYHOUSE_BISHOP_H

#include "../piece.h"

class bishop : public piece {
private:
public:
    bishop(player_type type);
	bishop(player_type type, side side);
	string to_string(style style);
	vector<move> get_possible_moves();
	bool see_king();
};


#endif //CRAZYHOUSE_BISHOP_H
