//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include <utility>

#include "move.h"

move::move(position from, position to) : from(std::move(from)), to(std::move(to)) {}

position move::get_from() const { return from; }
position move::get_to() const { return to; }

move::move(const string&& s) {
	this->from = position (toupper(s[0]), s[1]);
	this->to = position (toupper(s[2]), s[3]);
}

special_move move::get_special() const { return special; }

move::move(position from, position to, special_move special) : from(std::move(from)), to(std::move(to)), special(special) {}

string move::to_string() const {
	string s(4, ' ');
	s[0] = tolower(from.first);
	s[1] = from.second;
	s[2] = tolower(to.first);
	s[3] = to.second;

	return s;
}

bool move::operator == (const move& m) {
	return from == m.from && to == m.to && special == m.special;
}
