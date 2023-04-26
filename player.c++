//
// Created by Eduard Andrei Radu on 22.04.2023.
//


#include "player.h"
#include "table.h"
#include <vector>

#include "pieces/all_pieces.h"


player::player(player_type type) : type(type), pieces(vector<piece*>()) {
//	Put pieces on the table except pawns
	pieces.emplace_back(new king(type));
	pieces.emplace_back(new queen(type));
	pieces.emplace_back(new bishop(q, type));
	pieces.emplace_back(new bishop(k, type));
	pieces.emplace_back(new knight(q, type));
	pieces.emplace_back(new knight(k, type));
	pieces.emplace_back(new rook(q, type));
	pieces.emplace_back(new rook(k, type));

//	Put pawns on the table
	for (char i = 'A'; i <= 'H'; i++) {
		string digit = type == white ? "2" : "7";
		pieces.emplace_back(new pawn(string() + i + digit, type));
	}

// 	Update table
	std::for_each(pieces.begin(), pieces.end(), [](piece* p) {
		table::get_instance().set_piece(p, p->get_position());
	});
}

player::~player() = default;

vector<move> player::get_possible_moves() {
	vector<move> moves = {};

	for (piece* pc : pieces) {
		for (move m : pc->get_possible_moves()) {
			moves.emplace_back(m);
		}
    }

	return moves;
}

move player::make_move() {
//	TODO implement a better AI
	vector<move> moves = get_possible_moves();

	return moves[rand() % moves.size()];
}

