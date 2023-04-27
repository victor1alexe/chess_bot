//
// Created by Eduard Andrei Radu on 27.04.2023.
//

#ifndef CRAZYHOUSE_DEBUG_H
#define CRAZYHOUSE_DEBUG_H

#include "../board.h"

class debug {
private:
	static unsigned int debug_line;
	debug();
public:
	static void print_board();
	static void print_last_move();
	static void init_debug();
	static void print_possible_moves(piece* p);
};

#endif //CRAZYHOUSE_DEBUG_H
