#ifndef CRAZYHOUSE_KNIGHT_H
#define CRAZYHOUSE_KNIGHT_H

#include "../piece.h"

class knight : public piece {
private:
public:
	knight(player_type type, side side);
    knight(player_type type);
	string to_string(style style);
	vector<move> get_possible_moves();
	bool see_king();
};

#endif //CRAZYHOUSE_KNIGHT_H
