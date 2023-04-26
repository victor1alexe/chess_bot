//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#include "move.h"

move::move(pair<char, char> from, pair<char, char> to) {this->from = from;this->to = to;}

position move::get_from() { return from; }
position move::get_to() { return to; }

move::move(const string& s) {
	this->from = position (toupper(s[0]), s[1]);
	this->to = position (toupper(s[2]), s[3]);
}

string move::to_string() const {
	string s(4, ' ');
	s[0] = tolower(from.first);
	s[1] = from.second;
	s[2] = tolower(to.first);
	s[3] = to.second;

	return s;
}
