//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "rook.h"

rook::rook(player_type type, side side) : piece(type) {
	switch (type) {
		case WHITE:
			switch (side) {
				case QUEEN:
					set_default_position({'A', '1'});
					break;
				case KING:
					set_default_position({'H', '1'});
					break;
			}
			break;
		case BLACK:
			switch (side) {
				case QUEEN:
					set_default_position({'A', '8'});
					break;
				case KING:
					set_default_position({'H', '8'});
					break;
			}
			break;
	}
}

string rook::to_string(style style) {
	switch (style) {
		case BOT:
			return "R";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2656";
				case BLACK: return "\u265C";
			}
			break;
		default: break;
	}
}