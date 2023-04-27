//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "board.h"
#include "debug/debug.h"
#include "move.h"
#include <iostream>

using std::cout, std::endl;

int main() {
	board& b = board::get_instance();

	debug::init_debug();
	debug::print_board();

//	for (int i = 0; i < 200; ++i) {
//		vector<move> moves = b.get_white().get_possible_moves();
//		b.make_move(moves[rand() % moves.size()]);
//		debug::print_last_move();
//		debug::print_board();
//
//		moves = b.get_black().get_possible_moves();
//		b.make_move(moves[rand() % moves.size()]);
//		debug::print_last_move();
//		debug::print_board();
//	}

	vector<move> moves = b.get_white().get_possible_moves();
	b.make_move(move("D8D5"));
	debug::print_last_move();
	debug::print_board();

	moves = b.get_black().get_possible_moves();
	b.make_move(move("F1F3"));
	debug::print_last_move();
	debug::print_board();

	return 0;
}