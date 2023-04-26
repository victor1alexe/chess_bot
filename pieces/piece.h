//
// Created by Eduard Andrei Radu on 20.04.2023.
//

#ifndef CRAZYHOUSE_PIECE_H
#define CRAZYHOUSE_PIECE_H

#include <string>
#include <vector>
#include "../move.h"
#include "extra.h"

using std::string;
using std::vector;
using std::pair;

class piece {
private:
	player_type p;
	string name;
	pair<char, char> position;
public:
	explicit piece(player_type p);

	piece();

	player_type get_player();
	void set_name(string name);

	virtual void set_position(pair<char, char> pos);
	pair<char, char> get_position();
	virtual vector<move> get_possible_moves();

	string to_string();
};


#endif //CRAZYHOUSE_PIECE_H
