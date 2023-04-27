//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_KING_H
#define CRAZYHOUSE_KING_H

#include "../piece.h"

class king : public piece {
private:
	bool short_castle;
	bool long_castle;
public:
	king(player_type type);
	string to_string(style style);
	vector<move> get_possible_moves();
	bool see_king();

	bool can_short_castle() const;
	bool can_long_castle() const;
	void set_short_castle(bool short_castle);
	void set_long_castle(bool long_castle);
};


#endif //CRAZYHOUSE_KING_H
