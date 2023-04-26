#include <iostream>

#include "table.h"
#include "player.h"
#include "protocol/protocol.h"

using std::cout;
using std::endl;


// Main function
//int main() {
////	Set up the table, players and protocol
//	protocol p = protocol();
//	table t = table::get_instance();
//	player w = player(white);
//	player b = player(black);
//
////	Send the "xboard" command to indicate that the engine is ready to communicate using XBoard protocol
//	p.sendCommand("xboard");
//
////	Read commands from the GUI
//	while (true) {
////		Get the command
//		string command = p.readLine();
//// 		Handle the command
//		if 		(command == "xboard") 		{ p.handleXBoardCommand(); }
//		else if (command == "protover 2") 	{ p.handleProtoverCommand(); }
//		else if (command == "new") 			{ p.handleNewCommand(); }
//		else if (command == "go") 			{ p.handleGoCommand(); }
//		else if (command[0] == 'm')			{ p.handleMoveCommand(command); }
//		else if (command == "white")		{ table::getInstance().set_current_player(white); }
//		else if (command == "black")		{ table::getInstance().set_current_player(black); }
//		else if (command == "quit") 		{ exit(0); }
//	}
//}

auto main() -> int {
//	Get the table and players
	table t = table::get_instance();
	player w = t.getW();
	player b = t.getB();

//	Draw the board
	t.display();
	cout << endl;

	char c;
	while (true) {
//		Exit if the user enters 'x'
		std::cin >> c;
		if (c == 'x') { exit(0); }

//		Get the current player
		player_type p = t.get_current_player();
		switch (p) {
		case white:
			t.update_table(w.make_move());
			t.set_current_player(black);
			break;
		case black:
			t.update_table(b.make_move());
			t.set_current_player(white);
			break;
		}

//		Draw the board
		t.display();
	}
}