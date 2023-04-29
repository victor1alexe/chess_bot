//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_PIECE_H
#define CRAZYHOUSE_PIECE_H

#include <string>
#include <vector>
#include "move.h"

using std::string;
using std::vector;

using position = std::pair<char, char>;
string to_string(position p);

static position OUT = position('0', '0');

enum player_type { WHITE, BLACK };
enum style { BOT, DEBUG };
enum side { QUEEN, KING };

class piece {
private:
	player_type type;
	position default_position;
    bool promoted;
public:
	piece(player_type type);
	player_type get_type();
	void set_default_position(position position);
	position get_default_position();
    bool is_promoted();
    void set_promotion(bool promotion);
    void set_type(player_type type);

	virtual string to_string(style style);
	virtual vector<move> get_possible_moves();

	virtual bool get_to_king(move m);
	virtual bool see_king();
};

#endif //CRAZYHOUSE_PIECE_H
