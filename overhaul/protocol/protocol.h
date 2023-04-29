
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
    static void handleXBoardCommand();
// Function to handle the "protover" command
    static void handleProtoverCommand();
// Function to handle the "new" command
    static void handleNewCommand();
// Function to handle the "go" command
    static void handleGoCommand();
// Function to handle the "force" command
    static void handleForceCommand();
// Function to handle the "resign" command
    static void handleResignCommand();
// Function to handle the "move" command
    static void handleMoveCommand(const string& command);
// Function to set the player type
    static void handleTypeCommand(const string& player_type);
    static void handleQuitCommand();
};

#endif //CRAZYHOUSE_PROTOCOL_H