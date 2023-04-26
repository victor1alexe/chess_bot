//
// Created by Eduard Andrei Radu on 25.04.2023.
//


#ifndef CRAZYHOUSE_PROTOCOL_H
#define CRAZYHOUSE_PROTOCOL_H

#include <string>
using std::string;

// Class to handle the communication with the GUI
struct protocol {
// Function to send a command to the GUI
	static void sendCommand(const string &command);
// Function to read a line from the GUI
	static string readLine();
// Function to handle the "xboard" command
	void handleXBoardCommand();
// Function to handle the "protover" command
	void handleProtoverCommand();
// Function to handle the "new" command
	void handleNewCommand();
// Function to handle the "go" command
	void handleGoCommand();
// Function to handle the "force" command
	void handleForceCommand();
// Function to handle the "resign" command
	void handleResignCommand();
// Function to handle the "move" command
    void handleMoveCommand(const string& command);
};

#endif //CRAZYHOUSE_PROTOCOL_H