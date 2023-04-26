//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_ROOK_H
#define CRAZYHOUSE_ROOK_H

#include "../piece.h"

class rook : public piece {
private:
public:
	rook(player_type type, side side);
	string to_string(style style);
};


#endif //CRAZYHOUSE_ROOK_H
