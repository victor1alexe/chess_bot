//
// Created by Eduard Andrei Radu on 25.04.2023.
//

#include "protocol.h"

#include <iostream>
#include <string>
#include <sstream>
#include "../table.h"

using std::cout;
using std::endl;
using std::cin;
using std::stringstream;


//	Function to send a command to the GUI
void protocol::sendCommand(const string& command) {
	cout << command << endl;
	cout.flush();
}

//	Function to read a line from the GUI
string protocol::readLine() {
	string line;
	getline(cin, line);
	return line;
}

//	Function to handle the "xboard" command
void protocol::handleXBoardCommand() {
	sendCommand("feature myname='crazyhouse' done=1");
}

//	Function to handle the "protover" command
void protocol::handleProtoverCommand() {
	stringstream ss;
	ss << "feature usermove=1 done=1";
	sendCommand(ss.str());
}

//	Function to handle the "new" command
void protocol::handleNewCommand() {
// 	Reset the engine state
	table::get_instance().reset();
}

void protocol::handleMoveCommand(const string& command) {
//	Get the table
	table t = table::get_instance();
// 	Get the move from the command
    move m = command.substr(5);
//	Update the table
	t.update_table(m);
// 	Save the best move in the engine state
	m = t.make_move();
// 	Send the best move to the GUI
	stringstream ss;
	ss << "move " << m.to_string();
	sendCommand(ss.str());
}

//	Function to handle the "go" command
void protocol::handleGoCommand() {
// 	Save the best move in the engine state
	move bestMove = table::get_instance().make_move();
// 	Send the best move to the GUI
	stringstream ss;
	ss << "move " << bestMove.to_string();
	sendCommand(ss.str());
}