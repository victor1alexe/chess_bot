//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "pawn.h"

pawn::pawn(player_type type, char file) : piece(type), file(file) {
	switch (type) {
		case WHITE:
			set_default_position({file, '2'});
			break;
		case BLACK:
			set_default_position({file, '7'});
			break;
	}
}

string pawn::to_string(style style) {
	switch (style) {
		case BOT:
			return std::string(1, file) + (get_type() == WHITE ? std::string(1, '2') : std::string(1, '7'));
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2659";
				case BLACK: return "\u265F";
			}
			break;
		default: break;
	}
}