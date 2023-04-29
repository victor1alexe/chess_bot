//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "board.h"
#include "debug/debug.h"
#include "move.h"
#include <iostream>
#include <ctime>

using std::cout, std::endl;

int main() {
	srand(time(nullptr));
	board& b = board::get_instance();

	debug::init_debug();
	debug::print_board();

	for (int i = 0; i < 10000; i++) {
        if (b.get_moves_since_last_capture() >= 50) {
            cout << "Draw!"
                 << endl;
            break;
        }

		vector<move> moves = b.get_white().get_possible_moves();

		if (moves.empty() && b.get_white().is_in_check()) {
			cout << "Black wins!"
				 << endl;
			break;
		} else if (moves.empty()) {
			cout << "Draw!"
				 << endl;
			break;
		}
        move mv = moves[rand() % moves.size()];
        //cout << "About to move:" << mv.to_string() << endl;
		b.make_move(mv);
		debug::print_last_move();

		debug::print_board();
		if (b.get_black().is_in_check())
			cout << "Black is in check!" << endl;

		moves = b.get_black().get_possible_moves();
		if (moves.empty() && b.get_black().is_in_check()) {
			cout << "White wins!"
				 << endl;
			break;
		} else if (moves.empty()) {
			cout << "Draw!"
				 << endl;
			break;
		}
        mv = moves[rand() % moves.size()];
        //cout << "About to move:" << mv.to_string() << endl;
		b.make_move(mv);
		debug::print_last_move();

		debug::print_board();
		if (b.get_white().is_in_check())
			cout << "White is in check!" << endl;
	}

//	vector<move> moves = b.get_white().get_possible_moves();
//	b.make_move(move("D8C6"));
//	debug::print_last_move();
//	debug::print_board();
//
//	moves = b.get_black().get_possible_moves();
//	b.make_move(move("A2A3"));
//	debug::print_last_move();
//	debug::print_board();
//
//	b.make_move(move("D7D5"));
//	debug::print_last_move();
//	debug::print_board();
//
//	b.make_move(move("F1F3"));
//	debug::print_last_move();
//	debug::print_board();
//
//	b.is_valid_move(move("D5D4"));
//
//	debug::print_last_move();
//	debug::print_board();

//	b.make_move(move("C8H5"));
//	debug::print_last_move();
//	debug::print_board();
//
//	debug::print_possible_moves(b[{'E', '2'}]);

	return 0;
}