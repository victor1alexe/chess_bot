//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_MOVE_H
#define CRAZYHOUSE_MOVE_H

#include <string>

using std::string;
using std::pair;

class move {
private:
	pair<char, char> from;
	pair<char, char> to;
public:
	move(const string& s);
	move(pair<char, char> from, pair<char, char> to);
	~move() = default;

	pair<char, char> get_from() const;
	pair<char, char> get_to() const;
	string to_string() const;
};

#endif //CRAZYHOUSE_MOVE_H
