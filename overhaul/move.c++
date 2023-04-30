//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include "move.h"
#include "board.h"
#include "piece.h"
#include "pieces/king.h"

const move move::START = move(OUT, OUT);
const move move::LONG_CASTLE_WHITE = move({'E', '1'},{'G', '1'}, LONG_CASTLE);
const move move::LONG_CASTLE_BLACK = move({'E', '8'},{'G', '8'}, LONG_CASTLE);
const move move::SHORT_CASTLE_WHITE = move({'E', '1'},{'G', '1'}, SHORT_CASTLE);
const move move::SHORT_CASTLE_BLACK = move({'E', '8'},{'G', '8'}, SHORT_CASTLE);

move::move(position from, position to)
: 	from(std::move(from)),
	to(std::move(to)) {}

position move::get_from() const { return from; }
position move::get_to() const { return to; }

move::move(const string&& s) {
	this->from = position (toupper(s[0]), s[1]);
	this->to = position (toupper(s[2]), s[3]);
}

special_move move::get_special() const { return special; }

move::move(position from, position to, special_move special) : from(std::move(from)), to(std::move(to)), special(special) {}

string move::to_string() const {
    if (special == SHORT_CASTLE || special == LONG_CASTLE) {
        if ((*this) == move::LONG_CASTLE_WHITE) {
            return "e1c1";
        } else if ((*this) == move::SHORT_CASTLE_WHITE) {
            return "e1g1";
        } else if ((*this) == move::LONG_CASTLE_BLACK) {
            return "e8c8";
        } else if ((*this) == move::SHORT_CASTLE_BLACK) {
            return "e8g8";
        }
    }

    return string(1, tolower(from.first)) +
           string(1, from.second) +
           string(1, tolower(to.first)) +
           string(1, to.second);
}



bool move::operator == (const move& m) const {
	return from == m.from && to == m.to && special == m.special;
}
