//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "bishop.h"

bishop::bishop(player_type type, side side) : piece(type) {
	switch (type) {
		case WHITE:
			switch (side) {
				case QUEEN:
					set_default_position({'C', '1'});
					break;
				case KING:
					set_default_position({'F', '1'});
					break;
			}
			break;
		case BLACK:
			switch (side) {
				case QUEEN:
					set_default_position({'C', '8'});
					break;
				case KING:
					set_default_position({'F', '8'});
					break;
			}
			break;
	}
}

string bishop::to_string(style style) {
	switch (style) {
		case BOT:
			return "B";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2657";
				case BLACK: return "\u265D";
			}
			break;
		default: break;
	}
}