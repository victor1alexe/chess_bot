//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_PLAYER_H
#define CRAZYHOUSE_PLAYER_H

#include <vector>
#include "piece.h"

using std::vector;

class player {
private:
	player_type type;
	vector<piece*> pieces_on_board;
	vector<piece*> pieces_in_hand;
	bool in_check;
	piece* my_king;

	bool long_castle;
	bool short_castle;
public:
	player() = default;
	player(player_type type);
	player_type get_type();

	void add_piece(piece* p);
	void capture_piece(piece* p);

	void remove_piece(piece* p);
	void place_piece(piece* p);

    void set_long_castle(bool long_castle);
    void set_short_castle(bool short_castle);

    vector<piece*> get_pieces_in_hand() const;

	piece* get_king() const;

	void set_in_check(bool in_check);
	bool is_in_check() const;

	void init_pieces();
	auto begin() -> decltype(pieces_on_board.begin());
	auto end() -> decltype(pieces_on_board.end());
	piece* operator[](int index);
	vector<move> get_possible_moves() const;

	bool can_short_castle() const;
	bool can_long_castle() const;
};

#endif //CRAZYHOUSE_PLAYER_H
