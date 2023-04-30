//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "board.h"
#include "debug/debug.h"
#include "move.h"
#include <iostream>
#include <ctime>
#include "protocol/protocol.h"

using std::cout, std::endl;

void play_random() {
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
        cout << "_____" << endl;

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
        cout << "_____" << endl;
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

    //print pieces in hand for white
    cout << "White pieces in hand: ";
    for (auto& piece : b.get_white().get_pieces_in_hand()) {
        cout << piece->to_string(DEBUG) << " ";
    }
    cout << endl;

    //print pieces in hand for black
    cout << "Black pieces in hand: ";
    for (auto& piece : b.get_black().get_pieces_in_hand()) {
        cout << piece->to_string(DEBUG) << " ";
    }
    cout << endl;

}

void play_protocol() {
    // Send the "xboard" command to indicate that the engine is ready to communicate using XBoard protocol
    protocol::sendCommand("xboard");

    // Read commands from the GUI
    while (true) {
        string command = protocol::readLine();

        // Handle the command
        if (command == "xboard") {
            protocol::handleXBoardCommand();
        } else if (command == "protover 2") {
            protocol::handleProtoverCommand();
        } else if (command == "new") {
            protocol::handleNewCommand();
        } else if (command == "quit") {
            protocol::handleQuitCommand();
            exit(0);
        } else if (command == "go") {
            protocol::handleGoCommand();
        } else if (command == "white" || command == "black") {
            protocol::handleTypeCommand(command);
        } else if (command[0] == 'u') {
            protocol::handleMoveCommand(command);
        } else if (command == "force") {
            protocol::handleForceCommand();
        }
    }
}

int main() {
    play_random();
    //play_protocol();


	return 0;
}