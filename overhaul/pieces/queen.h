//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_QUEEN_H
#define CRAZYHOUSE_QUEEN_H

#include "../piece.h"

class queen : public piece {
private:
public:
	queen(player_type type);
	string to_string(style style);
};


#endif //CRAZYHOUSE_QUEEN_H
