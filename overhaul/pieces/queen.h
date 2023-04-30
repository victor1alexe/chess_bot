#ifndef CRAZYHOUSE_QUEEN_H
#define CRAZYHOUSE_QUEEN_H

#include "../piece.h"

class queen : public piece {
private:
public:
	queen(player_type type);
	string to_string(style style);
	vector<move> get_possible_moves();
	bool see_king();
};


#endif //CRAZYHOUSE_QUEEN_H
