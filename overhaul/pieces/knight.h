//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_KNIGHT_H
#define CRAZYHOUSE_KNIGHT_H

#include "../piece.h"

class knight : public piece {
private:
public:
	knight(player_type type, side side);
	string to_string(style style);
};


#endif //CRAZYHOUSE_KNIGHT_H
