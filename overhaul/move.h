//
// Created by Eduard Andrei Radu on 21.04.2023.
//

#ifndef CRAZYHOUSE_MOVE_H
#define CRAZYHOUSE_MOVE_H

#include <string>

using std::string;
using std::pair;
using position = pair<char, char>;

enum special_move { SHORT_CASTLE, LONG_CASTLE, EN_PASSANT, PROMOTION, NONE };

class move {
private:
	special_move special = NONE;
	position from;
	position to;
public:
	static const move START;
	static const move LONG_CASTLE_WHITE;
	static const move LONG_CASTLE_BLACK;
	static const move SHORT_CASTLE_WHITE;
	static const move SHORT_CASTLE_BLACK;
	explicit move(const string&& s);
	move(position from, position to);
	move(position from, position to, special_move special);
	~move() = default;

	position get_from() const;
	position get_to() const;
	special_move get_special() const;
	string to_string() const;
	bool operator == (const move& m) const;
};

#endif //CRAZYHOUSE_MOVE_H