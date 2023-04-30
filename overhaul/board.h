//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#ifndef CRAZYHOUSE_BOARD_H
#define CRAZYHOUSE_BOARD_H

#include <map>
#include "player.h"
#include <stack>

using std::map, std::stack;

struct backup {
	map<position, piece*> pieces_cp;
	map<piece*, position> positions_cp;
	stack <move> moves_cp;
	player white_cp;
	player black_cp;
	backup();
	~backup() = default;
};

class board {
private:
	static board* instance;
	map<position, piece*> pieces;
	map<piece*, position> positions;
	stack<move> moves;
    int moves_since_last_capture;
	player white;
	player black;
    player_type current_player;
    bool powered_on;
	backup* _backup;
	board();
public:
	board(board& other) = delete;
	static board& get_instance();
	position get_position(piece* piece);
	piece* get_piece(position position);
	map<position, piece*> get_pieces();
	map<piece*, position> get_positions();
    void set_powered_on(bool powered_on);
    bool is_powered_on() const;
	stack<move> get_moves();
	void display() const;
	void reset();

    player_type get_current_player() const;
    void set_current_player(player_type p_t);

	position& operator[](piece* piece);
	piece* operator[](position position);

	bool is_valid_move(move m);
	static bool is_in_bounds(position position);

	const move& get_last_move() const;

    player& get_white();
    player& get_black();

	void make_move(move m);
	bool would_be_check(move m);

	void make_backup();
	void restore();

    int get_moves_since_last_capture() const;
    void increment_moves_since_last_capture();
    void reset_moves_since_last_capture();

	bool is_castle_possible(player_type p_t, side s);
};



#endif //CRAZYHOUSE_BOARD_H
