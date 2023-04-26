//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "knight.h"

knight::knight(player_type type, side side) : piece(type) {
	switch (type) {
		case WHITE:
			switch (side) {
				case QUEEN:
					set_default_position({'B', '1'});
					break;
				case KING:
					set_default_position({'G', '1'});
					break;
			}
			break;
		case BLACK:
			switch (side) {
				case QUEEN:
					set_default_position({'B', '8'});
					break;
				case KING:
					set_default_position({'G', '8'});
					break;
			}
			break;
	}
}

string knight::to_string(style style) {
	switch (style) {
		case BOT:
			return "N";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2658";
				case BLACK: return "\u265E";
			}
			break;
		default: break;
	}
}