//
// Created by Eduard Andrei Radu on 25.04.2023.
//

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "protocol.h"
#include "../pieces/king.h"
#include "../board.h"
#include "../debug/debug.h"

using std::cout;
using std::endl;
using std::cin;
using std::stringstream;
using std::string;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base *>(ptr) != nullptr;
}

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
    string string_move = command.substr(9);
    if (instanceof<king>(b[{'e', '1'}])) {
        if (string_move == "e1g1") {
            b.make_move(move::SHORT_CASTLE_WHITE);
        } else if (string_move == "e1c1") {
            b.make_move(move::LONG_CASTLE_WHITE);
        }
    } else if (instanceof<king>(b[{'e', '8'}])) {
        if (string_move == "e8g8") {
            b.make_move(move::SHORT_CASTLE_BLACK);
        } else if (string_move == "e8c8") {
            b.make_move(move::LONG_CASTLE_BLACK);
        }
    } else {
        move m = move(command.substr(9));
        b.make_move(m);
    }
    //debug::print_board();

// 	Send the best move to the GUI
    if (b.is_powered_on()){
        srand(time(nullptr));
        if (b.get_current_player() == WHITE) {
            vector<move> moves = b.get_white().get_possible_moves();
            if (moves.empty() && !b.get_white().is_in_check()) {
                cout << "1/2-1/2 {Stalemate}" << endl;
                return;
            }
            else if (moves.empty() && b.get_white().is_in_check()) {
                cout << "0-1 {Black mates}" << endl;
                return;
            }

            move m1 = moves[rand() % moves.size()];
            b.make_move(m1);

            stringstream ss;
            ss << "move " << m1.to_string();
            sendCommand(ss.str());

        } else {
            vector<move> moves = b.get_black().get_possible_moves();

            if (moves.empty() && !b.get_black().is_in_check()) {
                cout << "1/2-1/2 {Stalemate}" << endl;
                return;
            }
            else if (moves.empty() && b.get_black().is_in_check()) {
                cout << "1-0 {White mates}" << endl;
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
        if (moves.empty() && !b.get_white().is_in_check()) {
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
        if (moves.empty() && !b.get_black().is_in_check()) {
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
}

void protocol::handleForceCommand() {
    board& b = board::get_instance();
    b.set_powered_on(false);
}
