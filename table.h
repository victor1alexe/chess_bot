//
// Created by Eduard Andrei Radu on 20.04.2023.
//

#ifndef CRAZYHOUSE_TABLE_H
#define CRAZYHOUSE_TABLE_H

//
// Created by Eduard Andrei Radu on 20.04.2023.
//

#include <array>
#include <map>

#include "player.h"
#include "pieces/piece.h"
#include "player.h"
#include "move.h"

using std::array;
using std::map;


class table {
private:
	static table t;
	map<pair<char, char>, piece*> pieces;
	player_type current_player;
	player w;
	player b;
	table();
public:
	~table() = default;
	void set_piece(piece* p,  pair<char, char> pos);
	static bool is_valid_move(const move& m);
	static table& get_instance();

	void set_current_player(player_type currentPlayer);
	player_type get_current_player() const;

	void update_table(move m);
	move make_move();
	void reset();
	void display() const;
	const player& getW() const;
	const player& getB() const;
	piece* at(pair<char, char> pos) const;
	piece*& operator[](pair<char, char> pos);
	void remove_piece(pair<char, char> pos);
};

#endif //CRAZYHOUSE_TABLE_H
