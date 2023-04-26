//
// Created by Eduard Andrei Radu on 20.04.2023.
//


#include <iostream>

#include "table.h"
#include "pieces/all_pieces.h"
#include "player.h"

using std::for_each;


table table::t = table();
table& table::get_instance() {return t;}

table::table() : pieces(map<pair<char, char>, piece *>()), b(player(black)), w(player(white)) {}

const player& table::getW() const {return w;}
const player& table::getB() const {return b;}

void table::set_piece(piece *p, pair<char, char> pos) {pieces[pos] = p;}
void table::remove_piece(pair<char, char> pos) {pieces.erase(pos);}

player_type table::get_current_player() const {return current_player;}
void table::set_current_player(player_type currentPlayer) {current_player = currentPlayer;}

piece*& table::operator[](pair<char, char> pos) {return pieces[pos];}

bool is_valid(pair<char, char> pos) {return pos.first >= 'A' && pos.first <= 'H' && pos.second >= 1 && pos.second <= 8;}
piece* table::at(pair<char, char> pos) const {try {return pieces.at(pos);} catch (const std::out_of_range& e) {return nullptr;}}

void table::display() const {
	for (int i = 8; i >= 1; i--) {
//		Print the row number
		std::cout << "|" << i << "|";

		for (char j = 'A'; j <= 'H'; j++) {
//			Print the pieces
			piece* p = at(pair<char, char>(j, i));
			if (p == nullptr)
				std::cout << " |";
			else
				std::cout << p->to_string() << "|";
		}
		std::cout << std::endl;
	}
//	Print the column letters
	std::cout << "| |A|☠|♨|☎|✂|☣|☺|✈|" << std::endl;
}

bool table::is_valid_move(const move& m) {
//	Get start and end positions
	const pair<char, char> to = m.get_to();
	const pair<char, char> from = m.get_from();

//	Get current player at start position
	player_type p = t.at(from)->get_player();

//	If the end position is out of bounds, return false
	bool in_bounds = is_valid(to);
	if (!in_bounds) return false;

//	If the end position is empty, return true
	bool is_empty = t.at(to) == nullptr;
	if(is_empty) return true;

//	If the end position is occupied by a piece of the same color, return false
	bool is_available = t.at(to)->get_player() != p;
	if (!is_available) return false;

//	TODO: check if the move would put the king in check
// 	If the move would put the king in check, return false
	bool would_be_in_check = false;

	return !would_be_in_check;
}

void table::reset() {
//	Clear the pieces map
	pieces.clear();

//	Create the pieces
	b = player(black);
	w = player(white);
}

void table::update_table(move m) {
//	Get start and end positions
	const pair<char, char> to = m.get_to();
	const pair<char, char> from = m.get_from();

//	Get the piece at the start position
	piece* p = pieces[from];

//	Set the piece at the end position
//	p->set_position(to);
	pieces[to] = p;

//	Clear the start position
	pieces.erase(from);
}

move table::make_move() {
//	Get the current player
	player_type p = get_current_player();

//	Return the move made by the current player
	return p == white ? w.make_move() : b.make_move();
}