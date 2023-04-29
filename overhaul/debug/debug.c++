//
// Created by Eduard Andrei Radu on 27.04.2023.
//

#include "debug.h"
#include "iostream"

using std::cout, std::endl;

unsigned int debug::debug_line = 1;

debug::debug() = default;

void debug::init_debug() {
	debug_line = 1;
	cout << "Debug step reset to 1." << endl << endl;
}

void debug::print_board() {
	board& board = board::get_instance();

	cout << "Step: " << debug_line << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	board.display();
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	debug_line++;
}

void debug::print_last_move() {
	board& board = board::get_instance();
	const move &m = board.get_last_move();
    switch (m.get_special()) {

        case LONG_CASTLE: {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Castled long." << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
                 << endl;
            break;
        }
        case SHORT_CASTLE: {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Castled short." << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
                 << endl;
            break;
        }
        default: {
            piece *p = board[m.get_to()];

            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            switch (p->get_type()) {
                case WHITE:
                    cout << "White moved ";
                    break;

                case BLACK:
                    cout << "Black moved ";
                    break;
            }

            cout << p->to_string(DEBUG)
                 << " (" << to_string(p->get_default_position()) << ")"
                 << " from " << to_string(m.get_from())
                 << " to " << to_string(m.get_to()) << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
                 << endl;
        }
    }
}

void debug::print_possible_moves(piece *p) {
	board& board = board::get_instance();
	if (p == nullptr) {
		for (auto& [_, piece] : board.get_pieces()) {
			cout << piece->to_string(DEBUG) << ' ' << to_string(piece->get_default_position()) << ' ';
			for (move& mv : piece->get_possible_moves()) {
				cout << mv.to_string() << ' ';
			}
			cout << endl;
		}
	} else {
		cout << p->to_string(DEBUG) << ' ' << p->get_default_position().first << p->get_default_position().second << ' ';
		vector<move> moves = p->get_possible_moves();
		std::for_each(moves.begin(), moves.end(), [&](const move &el) { cout << el.to_string() << ' '; });
		cout << endl;
	}
}