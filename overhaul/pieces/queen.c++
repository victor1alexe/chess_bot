//
// Created by Eduard Andrei Radu on 26.04.2023.
//

#include "queen.h"

queen::queen(player_type type) : piece(type) {
	switch (type) {
		case WHITE:
			set_default_position({'E', '1'});
			break;
		case BLACK:
			set_default_position({'E', '8'});
			break;
	}
}

string queen::to_string(style style) {
	switch (style) {
		case BOT:
			return "Q";
		case DEBUG:
			switch (get_type()) {
				case WHITE: return "\u2655";
				case BLACK: return "\u265B";
			}
			break;
		default: break;
	}
}