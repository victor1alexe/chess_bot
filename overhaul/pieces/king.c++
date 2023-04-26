//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "king.h"

king::king(player_type type) : piece(type) {
	switch (type) {
		case WHITE:
			set_default_position({'D', '1'});
			break;
		case BLACK:
			set_default_position({'D', '8'});
			break;
	}
}

string king::to_string(style style) {
	switch (style) {
		case BOT:
			return "K";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2654";
				case BLACK: return "\u265A";
			}
			break;
		default: break;
	}
}