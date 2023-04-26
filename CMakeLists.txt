cmake_minimum_required(VERSION 3.23)
project(CrazyHouse)

set(CMAKE_CXX_STANDARD 20)

add_executable(CrazyHouse
        overhaul/main.c++
        overhaul/board.c++
        overhaul/piece.c++
        overhaul/player.c++
        overhaul/pieces/pawn.c++
        overhaul/pieces/rook.c++
        overhaul/pieces/knight.c++
        overhaul/pieces/bishop.c++
        overhaul/pieces/queen.c++
        overhaul/pieces/king.c++
        )
