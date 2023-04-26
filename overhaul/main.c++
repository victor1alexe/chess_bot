//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "board.h"

int main() {
	const board& b = board::get_instance();
	b.display();
	return 0;
}