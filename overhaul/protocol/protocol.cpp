//
// Created by Eduard Andrei Radu on 25.04.2023.
//

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "protocol.h"
#include "../board.h"
#include "../debug/debug.h"

using std::cout;
using std::endl;
using std::cin;
using std::stringstream;
using std::string;

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
static std::string constructFeaturesPayload() {
    std::stringstream payload;
    payload << "feature"
            << " done=0"
            << " sigint=0"
            << " sigterm=0"
            << " san=0"
            << " reuse=0"
            << " usermove=1"
            << " analyze=0"
            << " ping=0"
            << " setboard=0"
            << " level=0"
            << " variants=\"normal\""
            << " name=\"" << "CrazyHouse" << "\" myname=\""
            << "CrazyHouse" << "\" done=1\n";
    return payload.str();
}
//	Function to handle the "xboard" command
void protocol::handleXBoardCommand() {
    //sendCommand(constructFeaturesPayload());
}

//	Function to handle the "protover" command
void protocol::handleProtoverCommand() {
    sendCommand(constructFeaturesPayload());
}

//	Function to handle the "new" command
void protocol::handleNewCommand() {
// 	Reset the engine state
    board::get_instance().reset();
}

void protocol::handleMoveCommand(const string& command) {
//	Get the board
    board& b = board::get_instance();
// 	Get the move from the command
//    string string_move = command.substr(5);
// TODO check castling

// 	Get the move from the command
    move m = move(command.substr(9));
//	Update the table
    b.make_move(m);

// 	Send the best move to the GUI
    if (b.is_powered_on()){
        srand(time(nullptr));
        if (b.get_current_player() == WHITE) {
            vector<move> moves = b.get_white().get_possible_moves();
            if (moves.empty()) {
                    cout << "1/2-1/2 {Stalemate}" << endl;
                return;
            }

            move m1 = moves[rand() % moves.size()];
            b.make_move(m1);

            stringstream ss;
            ss << "move " << m1.to_string();
            sendCommand(ss.str());

        } else {
            vector<move> moves = b.get_black().get_possible_moves();

            if (moves.empty()) {
                    cout << "1/2-1/2 {Stalemate}" << endl;
                return;
            }

            move m1 = moves[rand() % moves.size()];
            b.make_move(m1);

            stringstream ss;
            ss << "move " << m1.to_string();
            sendCommand(ss.str());
        }
    }
}

//	Function to handle the "go" command
void protocol::handleGoCommand() {
    board& b = board::get_instance();
    b.set_powered_on(true);
// 	Save the best move in the engine state
    srand(time(nullptr));
    if (b.get_current_player() == WHITE) {
        vector<move> moves = b.get_white().get_possible_moves();
        if (moves.empty()) {
                cout << "1/2-1/2 {Stalemate}" << endl;
            return;
        }

        move m = moves[rand() % moves.size()];
        b.make_move(m);

        stringstream ss;
        ss << "move " << m.to_string();
        sendCommand(ss.str());
    } else {
        vector<move> moves = b.get_black().get_possible_moves();
        if (moves.empty()) {
                cout << "1/2-1/2 {Stalemate}" << endl;
            return;
        }

        move m = moves[rand() % moves.size()];
        b.make_move(m);

        stringstream ss;
        ss << "move " << m.to_string();
        sendCommand(ss.str());
    }
}

void protocol::handleTypeCommand(const string& player_type) {
    board& b = board::get_instance();
    if (player_type == "white") {
        b.set_current_player(WHITE);
    } else if (player_type == "black") {
        b.set_current_player(BLACK);
    }
}

void protocol::handleQuitCommand() {
    // TODO: check if something else needs to be done
}
