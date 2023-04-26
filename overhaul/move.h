//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_MOVE_H
#define CRAZYHOUSE_MOVE_H

#include <string>

using std::string;
using std::pair;
using position = pair<char, char>;

class move {
private:
	position from;
	position to;
public:
	move(const string& s);
	move(position from, position to);
	~move() = default;

	position get_from();
	position get_to();
	string to_string() const;
};

#endif //CRAZYHOUSE_MOVE_H