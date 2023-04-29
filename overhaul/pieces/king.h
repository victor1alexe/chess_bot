//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_KING_H
#define CRAZYHOUSE_KING_H

#include "../piece.h"

class king : public piece {
private:
public:
	king(player_type type);
	string to_string(style style);
	vector<move> get_possible_moves();
	bool see_king();
};


#endif //CRAZYHOUSE_KING_H
