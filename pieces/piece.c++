//
// Created by Eduard Andrei Radu on 20.04.2023.
//

#include "piece.h"
#include <utility>
#include <vector>

using std::vector;

piece::piece() { p = player_type::white; }
piece::piece(player_type p) : p(p) {}
void piece::set_position(const pair<char, char> pos) { position = pos; }
pair<char, char> piece::get_position() { return position; }
player_type piece::get_player() { return p; }
vector<move> piece::get_possible_moves() { return {}; }
void piece::set_name(string piece_name) { name = std::move(piece_name); }
string piece::to_string() { return name; }