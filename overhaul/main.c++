//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "board.h"
#include <iostream>

using std::cout, std::endl;

int main() {
	board& b = board::get_instance();
	b.display();
	cout << endl;
	return 0;
}