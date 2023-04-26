//
// Created by Eduard Andrei Radu on 21.04.2023.
//


#include "move.h"


move::move(pair<char, char> from, pair<char, char> to) {this->from = from;this->to = to;}

pair<char, char> move::get_from() const {return this->from;}
pair<char, char> move::get_to() const {return this->to;}

move::move(const string& s) {
	this->from = pair<char, char>(toupper(s[0]), s[1] - '0');
	this->to = pair<char, char>(toupper(s[2]), s[3] - '0');
}

string move::to_string() const {
	pair<char, char> from = get_from();
	pair<char, char> to = get_to();

	string s(8, ' ');
	s[0] = tolower(from.first);
	s[1] = from.second + '0';
	s[2] = tolower(to.first);
	s[3] = to.second + '0';

	return s;
}