//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include <iostream>
#include "board.h"

using std::cout, std::endl;

board *board::instance = new board();

board& board::get_instance() {
	return *instance;
}

board::board() : white(WHITE), black(BLACK){
	reset();
}

position board::get_position(piece *piece) {
	return positions[piece];
}

piece *board::get_piece(position position) {
	if (pieces.find(position) == pieces.end()) {
		return nullptr;
	}
	return pieces[position];
}

void board::display() const {
	for (char i = '8'; i >= '1'; i--) {
		for (char j = 'A'; j <= 'H'; j++) {
			position pos = position(j, i);
			if (pieces.find(pos) == pieces.end()) {
				cout << " ";
			} else {
				cout << pieces.at(pos)->to_string(DEBUG);
			}
		}
		cout << endl;
	}
}

position& board::operator[](piece* piece) {
	return positions[piece];
}

piece*& board::operator[](position position) {
	return pieces[position];
}

void board::reset() {
	pieces = map<position, piece*>();
	positions = map<piece*, position>();

	white.init_pieces();
	black.init_pieces();

	for (auto& piece : white) {
		pieces[piece->get_default_position()] = piece;
		positions[piece] = piece->get_default_position();
	}

	for (auto& piece : black) {
		pieces[piece->get_default_position()] = piece;
		positions[piece] = piece->get_default_position();
	}

}